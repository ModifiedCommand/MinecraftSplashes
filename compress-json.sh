#!/bin/bash

for dir in ./**/**/; do
    mkdir "$dir"/min
    jq -c < "$dir/index.json" > "$dir/min/index.json"
done
