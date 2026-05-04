<?php


$template = "
#if __has_include(<lvgl.h>) && LV_FONT_%s
    const LVGLfont lvFont%s = {&lv_font_%s};
#else 
    const LVGLfont lvFont%s = {&lgfx_lv_font_%s};
#endif
";


function toGamelleCase($in)
{
  $in = str_replace("_", " ", $in);
  $in = ucwords(strtolower($in));
  $in = str_replace(" ", "", $in);
  return $in;
}


$files = glob("*.c");

$extern = "";

foreach($files as $file)
{
  $c = file_get_contents($file);
  if(!preg_match("/#define LGFX_LV_FONT_([A-Z0-9_]+)/", $c, $matches))
    die("reg failed for $file".PHP_EOL);
  if(count($matches)!=2)
    die("empty capture for $file".PHP_EOL);
  $nameCaps = $matches[1];
  $nameLow  = strtolower($nameCaps);
  $nameGam  = toGamelleCase($nameCaps);
  echo sprintf($template, $nameCaps, $nameGam, $nameLow, $nameGam, $nameLow);

  $extern .= sprintf("extern const lgfx::LVGLfont lvFont%s;".PHP_EOL, $nameGam);
  
  //echo $matches[1].PHP_EOL;
  //print_r($matches);exit;
  
}


echo $extern;





