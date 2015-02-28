<?php

function arava_center_preprocess_html(&$vars) {
  global $language;
  $vars['classes_array'][] = $language->dir;
}

function arava_center_preprocess_page(&$vars) {
  if ((arg(0) == 'registration' && arg(1) == 'thanks') || arg(0) == 'my_timetable' || arg(0) == 'health-form' || arg(0) == 'close-dialog') {
    $vars['theme_hook_suggestions'][] = 'page__blank';
  }
  if (arg(0) == 'file' && arg(1) == 'swf') {
    if (isset($_COOKIE['moar_file_restriction'])) {
      if ($_COOKIE['moar_file_restriction'] == arg(3)) {
        $vars['theme_hook_suggestions'][] = 'page__blank_full';
      }
    }
  }
  if (arg(0) == 'registration' || arg(0) == 'user' || arg(0) == 'my_timetable' || arg(0) == 'semester-timetable' || arg(0) == 'health-form') {
    drupal_add_css(path_to_theme() . '/css/registration.css');
  }
}

function arava_center_preprocess_user_profile(&$vars) {
  unset($vars['user_profile']['mimemail']);
}
