<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<!--section starts-->
<?php if (!empty($title)): ?>
	<?php print $title; ?>
<?php endif; ?>
<!--rows start-->
<?php foreach ($rows as $id => $row): ?>
	<!--new row-->
	<div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
		<?php print $row; ?>
	</div>
<?php endforeach; ?>
<!--rows end-->