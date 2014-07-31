<?php if (!$label_hidden) : ?>
<div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
<?php endif; ?>

<?php
// Reduce number of images in teaser view mode to single image
if ($element['#view_mode'] == 'teaser') : ?>
<div class="field-item field-name-field-mt-photo even overlayed"<?php print $item_attributes[0]; ?>><?php print render($items[0]); ?></div> 
<?php return; endif; ?>

<?php $node=$element['#object']; $lang="und"; ?>
    <div class="field-name-field-mt-photo overlayed plus">
        <a class="image-popup" href="<?php print file_create_url($node->field_mt_photo[$lang][0]['uri']); ?>" title="<?php print $node->title; ?>">
            <img src="<?php print image_style_url('mt_photo', $node->field_mt_photo[$lang][0]['uri']); ?>" alt="<?php print $node->field_mt_photo[$lang][0]['alt']; ?>" title="<?php print $node->field_mt_photo[$lang][0]['title']; ?>"/>
        </a>
    </div>
<?php
drupal_add_js(drupal_get_path('theme', 'scholarly') .'/js/magnific-popup/jquery.magnific-popup.js', array('preprocess' => false));
drupal_add_css(drupal_get_path('theme', 'scholarly') . '/js/magnific-popup/magnific-popup.css');

drupal_add_js('
    jQuery(document).ready(function($) {
        $(window).load(function() {

			$(".image-popup").magnificPopup({
			type:"image",
			removalDelay: 300,
			mainClass: "mfp-fade",
			gallery: {
			enabled: true, // set to true to enable gallery
			}
			});

        });
    });',array('type' => 'inline', 'scope' => 'footer', 'weight' => 3)
);
?>