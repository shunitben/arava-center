<?php

function arava_center_preprocess_html(&$vars) {
  global $language;
  $vars['classes_array'][] = $language->dir;
}

function arava_center_preprocess_page(&$vars) {
  if ((arg(0) == 'registration' && arg(1) == 'thanks') || arg(0) == 'my_timetable' ) {
    $vars['theme_hook_suggestions'][] = 'page__blank';
  }
  if (arg(0) == 'registration' || arg(0) == 'user' || arg(0) == 'my_timetable') {
    drupal_add_css(path_to_theme() . '/css/registration.css');
  }
}

function arava_center_preprocess_user_profile(&$vars) {
  unset($vars['user_profile']['mimemail']);
}