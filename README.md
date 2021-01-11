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
    sudo make install

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

So to optimise a CSS file and send the output to screen use

    csstidy mycssfile.css

If you want to save the output to a file, use

    csstidy mycssfile.css myoutputfile.css

If you use the filename "-", CSSTidy reads from stdin.
To change settings, you have to add "--thesettingyouwanttochange=true or false" after the input file. If "true" is first in the syntax description, this indicates that "true" is the default value (the same applies to false). Example:

    csstidy mycssfile.css --remove_last_semicolon=true myoutputfile.css


## Original Description

### Introduction

CSSTidy is an opensource CSS parser and optimiser. It is available as executeable file (available for Linux, OSX and more) which can be controlled per command line and as PHP script (both with almost the same functionality).
In opposite to most other CSS parsers, no regular expressions are used and thus CSSTidy has full CSS2 support and a higher reliability.

Features ("a" stands for all selectors, "margin" stands for all properties):

   * colours like "black" or rgb(0,0,0) are converted to #000000 or rather #000 if possible. Some hex-codes are replaced by their colour names if they are shorter.
   * a{property:x;property:y;} becomes a{property:y;} (all duplicate properties are merged)
   * margin:1px 1px 1px 1px; becomes margin:1px;
   * margin:0px; becomes margin:0;
   * a{margin-top:10px; margin-bottom:10px; margin-left:10px; margin-right:10px;} becomes a{margin:10px;}
   * margin:010.0px; becomes margin:10px;
   * all unnecessary whitespace is removed, depending on the compression-level
   * all background-properties are merged
   * all comments are removed
   * the last semicolon in every block can be removed
   * missing semicolons are added, incorrect newlines in strings are fixed, missing units are added, bad colors (and color names) are fixed
   * property:value ! important; becomes property:value !important;

### Why optimise?

If you optimise your CSS code you have faster loading pages and lower traffic costs. So both you and your visitors benefit from an optimisation. If you are interested in a faster loading webpage, websiteoptimization.com might also be an interesting resource.

### Compression ratio

The compression ratio mostly depends on the level of whitespace-removal. Using standard whitespace-removal (which preserves the readability) the compression ratio often is 30% and more. In theory the compression ratio can be 99,99% but only very "stupid" stylesheets will allow those ratios. Also have a look at the examples.

### Apart from compression

If a high compression is not important for you, you can also use CSSTidy to format or fix CSS code for a higher browser compatibility. Apart from the 4 default templates you can specify custom templates so that you can easily format a lot of CSS code using your own coding style. Other features are sorting and changing the case of selectors and properties.

