<?php if (!$label_hidden) : ?>
<div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
<?php endif; ?>

<?php
// Reduce number of images in teaser view mode to single image
if ($element['#view_mode'] == 'teaser') : ?>
<div class="field-item field-type-image even"<?php print $item_attributes[0]; ?>><div class="overlayed"><?php print render($items[0]); ?></div></div> 
<?php return; endif; ?>

<?php $node=$element['#object']; $lang="und"; ?>

<div class="images-container clearfix">

    <div class="image-preview">
    <div class="overlayed large plus">
        <a class="image-popup" href="<?php print file_create_url($node->field_image[$lang][0]['uri']); ?>" title="<?php print $node->field_image[$lang][0]['title']; ?>">
            <img src="<?php print image_style_url('large', $node->field_image[$lang][0]['uri']); ?>" alt="<?php print $node->field_image[$lang][0]['alt']; ?>" title="<?php print $node->field_image[$lang][0]['title']; ?>"/>
        </a>
    </div>
    
    <?php if ($node->field_image[$lang][0]['title']) :?>
    <div class="image-caption clearfix">
        <?php if ($node->field_image[$lang][0]['title']) :?>
        <p><?php print $node->field_image[$lang][0]['title']; ?></p>
        <?php endif; ?>
    </div>
    <?php endif; ?>

    </div>

	<?php $numberOfImages=0; foreach ($node->field_image[$lang] as $key=>$file) { $numberOfImages++; } ?>  
    
    <?php if ($numberOfImages>1) { ?>  
        
        <div class="image-listing-items">
        <?php $i=0; foreach ($node->field_image[$lang] as $key=>$file) { 
        if ($key==0) { continue; } 
        $i++; ?>
        <div class="image-listing-item overlayed small plus">
            <a class="image-popup" href="<?php print file_create_url($node->field_image[$lang][$key]['uri']) ?>" title="<?php print $node->field_image[$lang][$key]['title']; ?>">
            <img src="<?php print image_style_url('small', $node->field_image[$lang][$key]['uri']); ?>" alt="<?php print $node->field_image[$lang][$key]['alt']; ?>" title="<?php print $node->field_image[$lang][$key]['title']; ?>"/>
            </a>
        </div>  
        <?php } ?>
        
        </div> 
    <?php } ?>

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