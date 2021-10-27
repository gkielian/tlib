#!/usr/bin/env python3
""" Parse the opcodes-rvv file to create 'instname opcode' output to stdout """

import argparse
import re

# matches vector instructions, e.g. "vadd.vv", "vrgather.vi"
vector_op_match = re.compile("^v.*")

# matches alphanumeric fields, e.g. "rs1", "rs2", "zimm10", "nf", ...
is_non_op_field = re.compile("^[a-z].*")

# matches all subfields with bit ranges, e.g. "31..26=0x0c"
is_bit_range = re.compile("^[0-9]*\.\.[0-9].*")

# matches subfields with single bit, e.g. "30=1", "31=0", ...
is_single_bit = re.compile(".*[0-9]=[0-9]$")

# matches binary string (e.g. "0011")
is_binary_string = re.compile("^[01].*$")

def mask_decoded_fields(line):
    """replace all decoded fields with 1's"""
    tokens = line.strip().split()
    for i in range(1, len(tokens)):
        if is_binary_string.match(tokens[i]):
          tokens[i] = re.sub(r'0', '1', tokens[i])
    return (" ").join(tokens)

def find_non_op_fields(line):
    """Substitutes non-opcode fields (e.g. vd, rs1, etc) with zeros"""
    tokens = line.strip().split()
    # print(tokens)
    for i in range(1, len(tokens)):
        if is_non_op_field.match(tokens[i]):
            if tokens[i] == "nf":
                tokens[i] = "000"
            if tokens[i] == "rd":
                tokens[i] = "00000"
            if tokens[i] == "rs1":
                tokens[i] = "00000"
            if tokens[i] == "rs2":
                tokens[i] = "00000"
            if tokens[i] == "simm5":
                tokens[i] = "00000"
            if tokens[i] == "vd":
                tokens[i] = "00000"
            if tokens[i] == "vm":
                tokens[i] = "0"
            if tokens[i] == "vs1":
                tokens[i] = "00000"
            if tokens[i] == "vs2":
                tokens[i] = "00000"
            if tokens[i] == "vs3":
                tokens[i] = "00000"
            if tokens[i] == "wd":
                tokens[i] = "0"
            if tokens[i] == "zimm":
                tokens[i] = "00000"
            if tokens[i] == "zimm10":
                tokens[i] = "0000000000"
            if tokens[i] == "zimm11":
                tokens[i] = "00000000000"
    return (" ").join(tokens)


def find_bit_range_fields(line):
    """find bit range containing fields, and then substitute with a string of the field value in binary"""
    tokens = line.strip().split()
    for i in range(1, len(tokens)):
        if is_bit_range.match(tokens[i]):
            bit_range = tokens[i].split("=")[0]
            hex_val = tokens[i].split("=")[1]
            start_bit = int(bit_range.split("..")[0])
            end_bit = int(bit_range.split("..")[1])
            tot_bits = start_bit - end_bit + 1
            format_str = "{:0" + str(tot_bits) + "b}"
            # print(bit_range, hex_val, start_bit, end_bit)

            # format with proper number of leading zeros
            bit_val = format_str.format(int(hex_val, base=16))
            # bit_val = str(bin(int(hex_val,0))[-tot_bits:])
            tokens[i] = bit_val
    return (" ").join(tokens)


def find_single_bits(line):
    """find single bit containing fields, and then substitute with a string of the field value in binary"""
    tokens = line.strip().split()
    for i in range(1, len(tokens)):
        if is_single_bit.match(tokens[i]):
            tokens[i] = tokens[i].split("=")[1]
    return (" ").join(tokens)


def combine_bitstring(line):
    """Joins all bit fields into single bit string"""
    tokens = line.strip().split()
    bit_string = "".join(tokens[1:])
    return tokens[0] + " " + bit_string


def convert_bits(line, base, no_prefix):
    """Converts and formats the binary string into requested base"""
    tokens = line.strip().split()
    bit_string = "".join(tokens[1:])

    if base == "binary":
        if no_prefix:
            return tokens[0] + " " + str(bit_string)
        else:
            return tokens[0] + " 0b" + str(bit_string)
        return line

    if base == "decimal":
        dec_val = str(int(bit_string, 2))
        return tokens[0] + " " + dec_val

    if base == "hex":
        hex_val = "{:08x}".format(int(bit_string, base=2))
        if no_prefix:
            return tokens[0] + " " + hex_val
        else:
            return tokens[0] + " 0x" + hex_val


def count_bits(line):
    """Prepends the number of characters within the bit_string, should be 32 for each line in binary representation"""
    tokens = line.strip().split()
    bit_string = "".join(tokens[1:])
    return str(len(bit_string)) + " " + tokens[0] + " " + bit_string


def main():
    """Parse opcodes-rvv to create "instname opcode" output to stdout"""

    parser = argparse.ArgumentParser(
        description="Parse opcodes-rvv to create instname, opcode output to stdout Download IREE host compiler from snapshot releases"
    )

    parser.add_argument(
        "--base",
        choices=["binary", "decimal", "hex"],
        default="binary",
        help="select base of output opcode binary, decimal or hex.",
    )

    parser.add_argument(
        "--no-prefix",
        action="store_true",
        help="disable to add prefix to binary and hex representations",
    )

    parser.add_argument(
        "--vector-mask",
        action="store_true",
        help="Produce mask per instruction for zero-ing non-opcode elements (e.g. zero-ing rs1,rs2, vs1, vs2, etc.)",
    )

    args = parser.parse_args()

    if args.vector_mask:
      with open("opcodes-rvv", "r") as rvv_opcode_list:
          for line in rvv_opcode_list:
              if vector_op_match.match(line):
                  line = find_bit_range_fields(line)
                  line = find_single_bits(line)
                  line = mask_decoded_fields(line) # turns op_fields to one's
                  line = find_non_op_fields(line)
                  line = combine_bitstring(line)
                  line = convert_bits(line, args.base, args.no_prefix)
                  print(line)
    else:
      with open("opcodes-rvv", "r") as rvv_opcode_list:
          for line in rvv_opcode_list:
              if vector_op_match.match(line):
                  line = find_non_op_fields(line)
                  line = find_bit_range_fields(line)
                  line = find_single_bits(line)
                  line = combine_bitstring(line)
                  line = convert_bits(line, args.base, args.no_prefix)
                  print(line)


if __name__ == "__main__":
    main()
