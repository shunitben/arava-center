<?php
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php print $wrapper_prefix; ?>
  <?php if (!empty($title)) : 
//$vid = 1;
//$tid = db_query("select tid from {taxonomy_term_data} where vid=:vid and name=:name", array(':vid' => $vid, ':name' => $title))->fetchField();
//print '<input type="hidden" class="catalog-term" name="catalog-term['.$tid.']" value="'.$tid.'">';  
  ?>
    <h3><?php 
if(user_access('administer nodes')){
	print '<div class="handle"></div>';
}
	print $title; ?></h3>
  <?php endif; ?>
  <?php print $list_type_prefix; ?>
    <?php foreach ($rows as $id => $row): ?>
      <li class="<?php print $classes_array[$id]; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
  <?php print $list_type_suffix; ?>
<?php print $wrapper_suffix; ?>
