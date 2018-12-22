# csstidy

The continuing story of Floele's project csstidy (C++ version)

## Based on

This repo is based on the last official csstidy C++ version 1.3 as of 2007-07-10 (file timestamp) / 2007-07-19 (announcement of 1.3) on [csstidy SF homepage](http://csstidy.sourceforge.net/changelog.php).

## Changes to original code

List of example fixes:
   * update to CSS3
   * do not remove tokens after media selector
   * remaining comments in selector are also removed
   * do not remove quotes on font-face subvalue format; chrome/iron ignores it but firefox needs the quotes

Improvements:
   * added man page by Kevin Coyner
   * added option strip_all_comments
   * Unnecessary dependency SCons was removed

## Requirements

   * make (no SCons anymore)
   * C++ compiler – g++ or MinGW

## Install

    git clone https://github.com/csstidy-c/csstidy.git
    cd csstidy
    make
    sudo cp release/csstidy/csstidy /usr/local/bin/
    sudo gzip -9 <csstidy/csstidy.1 >/usr/local/man/man1/csstidy.1.gz

## Usage

    csstidy input_filename [
        --allow_html_in_templates=[false|true] |
        --compress_colors=[true|false] |
        --compress_font_weight=[true|false] |
        --discard_invalid_properties=[false|true] |
        --lowercase_s=[false|true] |
        --preserve_css=[false|true] |
        --remove_backslash=[true|false] |
        --remove_last_semicolon=[false|true] |
        --silent=[false|true] |
        --sort_properties=[false|true] |
        --sort_selectors=[false|true] |
        --timestamp=[false|true] |
        --merge_selectors=[2|1|0] |
        --case_properties=[0|1|2] |
        --optimise_shorthands=[1|2|0] |
        --template=[default|filename|low|high|highest] |
        --strip_all_comments=[false|true] |
        output_filename ]*

