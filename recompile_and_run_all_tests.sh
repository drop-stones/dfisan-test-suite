#!/bin/sh

cd base_build && ninja clean && ninja -j8 && python3 ../utils/average.py -n 5 -o baseline.json
cd ../dfisan_base_build && ninja clean && ninja -j8 && python3 ../utils/average.py -n 5 -o dfisan_base.json
cd ../dfisan_build && ninja clean && ninja -j8 && python3 ../utils/average.py -n 5 -o dfisan.json
cd ../dfisan_unaligned_build && ninja clean && ninja -j8 && python3 ../utils/average.py -n 5 -o dfisan_unaligned.json

