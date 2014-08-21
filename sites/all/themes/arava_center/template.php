<?php

function arava_center_preprocess_html(&$vars) {
  global $language;
  $vars['classes_array'][] = $language->dir;
}

function arava_center_preprocess_page(&$vars) {
  if (arg(0) == 'registration' && arg(1) == 'thanks') {
    $vars['theme_hook_suggestions'][] = 'page__blank';
  }
  if (arg(0) == 'registration') {
    drupal_add_css(path_to_theme() . '/css/registration.css');
  }
}

function arava_center_preprocess_user_profile(&$vars) {
  unset($vars['user_profile']['mimemail']);
}