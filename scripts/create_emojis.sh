#!/bin/bash

# Copyright 2026 tobozo
#
# https://github.com/tobozo
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the “Software”), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


if [[ "$1" == "" ]]; then
  echo
  echo "Usage:"
  echo
  echo " ./`basename $0` path/to/NotoColorEmoji.ttf"
  echo
  exit
fi

fontFile=$1

# check if font file exists
if [[ ! -f "$fontFile" ]]; then
  echo "Font file not found: ${fontFile}"
  exit
fi


ifStatusFail () {
  status=$?
  if [ $status -ne 0 ]; then
    echo
    echo "Error:"
    if [ "$1" != "" ]; then
      echo $1
    fi
    if [ "$2" != "" ]; then
      echo $2
    fi
    if [ "$3" != "" ]; then
      echo $3
    fi
    echo
    exit
  fi
}



# check if php is available
has_php=`which php`
ifStatusFail "php not found"
# check if python is available
has_python=`which python3`
ifStatusFail "python3 not found"
# check if pip is available
has_pip=`which pip`
ifStatusFail "pip not found"
# check if fonttools is available in pip
fonttool_ver=`pip list | grep fonttools`
ifStatusFail "python module 'fonttools' not found"
# check if pillow is available in pip
pillow_ver=`pip list | grep pillow`
ifStatusFail "python module 'pillow' not found"
# check if resvg-python is available in pip
pillow_ver=`pip list | grep resvg-python`
status=$?
if [ $status -ne 0 ]; then
  echo "Warning: python module 'resvg-python' not found -> no support for SVG fonts"
fi

pngquant_ver=`which pngquant`
ifStatusFail " not found"


# generate emoji files for all sizes
for pngSize in "8" "16" "24" "32" "64"
do
  echo "Generating package for $pngSize x $pngSize emojis"

  pythoncmd=`printf "python3 extract_emoji.py %s --resize %s --output png%sx%s" "${fontFile}" $pngSize $pngSize $pngSize`
  echo "  1) Extract to png -> $pythoncmd"
  out=`$pythoncmd`
  ifStatusFail "python3 command failed:" $pythoncmd

  pngquantcmd=`printf "pngquant --force 8 png%sx%s/* --ext .png" $pngSize $pngSize`
  echo "  2) Uglify: reduce palette to 8 colors (including alpha) -> $pngquantcmd"
  out=`$pngquantcmd`
  ifStatusFail "pngquant command failed:" $pngquantcmd
  # find . -name '*.png' -exec pngquant --ext .png --force 16 {} \;

  phpcmd=`printf "php export_emoji_to_C.php %s" $pngSize`
  echo "  3) Export to C -> $phpcmd"
  out=`$phpcmd`
  ifStatusFail "php command failed:" $phpcmd

  cleanupcmd=`printf "rm -Rf png%sx%s" $pngSize $pngSize`
  echo "  4) Cleanup -> $cleanupcmd"
  out=`$cleanupcmd`
  ifStatusFail "cleanup command failed:" $cleanupcmd

  srcfolder=`printf "%sx%s" $pngSize $pngSize`
  dstfolder=`printf "../src/Fonts/emojis/%s" $srcfolder`

  [[ -d "$dstfolder" ]] && rm -Rf "$dstfolder" # remove if exists, mv is just rename under the hood

  movecmd=`printf "mv %s %s" $srcfolder $dstfolder`
  echo "  5) Deploy -> $movecmd"
  out=`$movecmd`
  ifStatusFail "move command failed:" $movecmd

done

echo "Deploying leftover files"

movecmd="mv emojis.h ../src/Fonts/emojis/"
echo "  1) Deploy -> $movecmd"
out=`$movecmd`
ifStatusFail "move command failed:" $movecmd

movecmd="mv emojis_structs.h ../src/Fonts/emojis/"
echo "  2) Deploy -> $movecmd"
out=`$movecmd`
ifStatusFail "move command failed:" $movecmd

movecmd="mv ReadMe.emojis.md ../"
echo "  3) Deploy -> $movecmd"
out=`$movecmd`
ifStatusFail "move command failed:" $movecmd


rm all_emojis.json
