<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php

// have a comma for each day of the week, for easier excel processing.

$allowed_values = $field->field_info['settings']['allowed_values'];
$field_values = $row->field_field_days_present;
$values = array();
foreach ($field_values as $field_value) {
  $values[$field_value['raw']['value']] = 1;
}
$output = '';

foreach ($allowed_values as $key => $allowed_value) {
  if (isset($values[$key])) {
    $output .= $allowed_value . ',';
  }
  else {
    $output .= ' ,';
  }
}

print $output;
?>