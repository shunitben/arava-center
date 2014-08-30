<?php

function arava_registration_timetable_page() {
  $output = '<div class=print-link><a href="javascript:window.print();">' . t('print') . '</a></div>';
  $output .= _arava_registration_generate_all_timetables();
 return $output;
}
