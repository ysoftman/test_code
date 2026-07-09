#!/bin/bash
echo "AND"
echo $((0 & 0))
echo $((0 & 1))
echo $((1 & 0))
echo $((1 & 1))

echo "OR"
echo $((0 | 0))
echo $((0 | 1))
echo $((1 | 0))
echo $((1 | 1))

echo "XOR"
echo $((0 ^ 0))
echo $((0 ^ 1))
echo $((1 ^ 0))
echo $((1 ^ 1))

echo "NOT"
echo $((~0))
echo $((~1))

echo "Left Shift"
echo $((1 >> 2))
echo $((10 >> 3))

echo "Right Shift"
echo $((1 << 2))
echo $((10 << 3))
