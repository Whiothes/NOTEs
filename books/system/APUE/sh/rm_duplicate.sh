#!/usr/bin/env bash

set -e

for f in $(find . -regex '.*(fig|ex).*\.c'); do
    echo $f
done
