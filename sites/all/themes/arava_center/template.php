<?php

function arava_center_preprocess_page(&$vars) {
  if (arg(0) == 'registration' && arg(1) == 'thanks') {
    $vars['theme_hook_suggestions'][] = 'page__blank';
  }
}