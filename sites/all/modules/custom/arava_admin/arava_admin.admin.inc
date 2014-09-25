<?php

/**
 * Administration area
 */
function arava_admin_page() {
  return theme('links', array('links' => array(

    'courses' => array(
      'title' => t('Courses'),
      'href' => 'admin/admin-courses',
    ),

    'accommodation' => array(
      'title' => t('Accommodation'),
      'href' => 'admin/admin-accommodation',
    ),

    'meals' => array(
      'title' => t('Meals'),
      'href' => 'admin/admin-meals',
    ),

    'presence' => array(
      'title' => t('Presence'),
      'href' => 'admin/admin-presence',
    ),

    'registration' => array(
      'title' => t('Registration'),
      'href' => 'admin/admin-registration',
    ),

  )));
}