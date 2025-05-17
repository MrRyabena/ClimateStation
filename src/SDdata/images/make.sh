#!/bin/bash

# Define variables
CONVERTER_PATH="../../scripts/image_to_file/image_to_file" # Path to the converter program (executable)
SOURCE_DIR="source"  # Directory containing input files
DEST_DIR="drain"     # Directory for the output files
INPUT_EXTENSION=".txt" # Input file extension
OUTPUT_EXTENSION=".shsf" # Output file extension

# Compile the program if it hasn't been compiled yet
if [ ! -f "$CONVERTER_PATH" ]; then
    echo "Compiling $CONVERTER_PATH.cpp..."
    g++ -o "$CONVERTER_PATH" "$CONVERTER_PATH.cpp"
    if [ $? -ne 0 ]; then
        echo "Compilation failed."
        exit 1
    fi
    echo "Compilation successful."
fi

# Generate output files from all input files in the source directory
shopt -s nullglob # Enable nullglob to handle no matches gracefully
for input_file in "$SOURCE_DIR"/*"$INPUT_EXTENSION"; do
    if [ -f "$input_file" ]; then
        echo "Processing $input_file..."
        "$CONVERTER_PATH" "$input_file" --output "${input_file%$INPUT_EXTENSION}$OUTPUT_EXTENSION"
    else
        echo "No input files found."
    fi
done

# Move generated files to the destination directory
echo "Moving generated files to $DEST_DIR..."
shopt -s nullglob # Enable nullglob to handle no matches gracefully
if mv "$SOURCE_DIR"/*"$OUTPUT_EXTENSION" "$DEST_DIR"; then
    echo "All files have been processed and moved to $DEST_DIR."
else
    echo "No generated files to move."
fi