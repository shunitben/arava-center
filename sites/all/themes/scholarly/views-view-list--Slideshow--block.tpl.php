<?php $caption_style = theme_get_setting('caption_style');?>

<div id="slideshow" class="main-slider <?php print $caption_style; ?>">

    <div class="flexslider">
        <ul class="slides">
        <?php foreach ($rows as $id => $row) { ?>
        <li>
        
        <?php $view = views_get_current_view();
        $nid = $view->result[$id]->nid; 
        $node = node_load($nid);
        $lang = 'und';
        
        if ($node->type=='mt_slideshow_entry') {
        
            if ($node->field_teaser_image) {
            
                $image = image_style_url('slideshow', $node->field_teaser_image[$lang][0]['uri']); 
                $title = $node->field_teaser_image[$lang][0]['title'];
                $alt = $node->field_teaser_image[$lang][0]['alt']; ?>
            
                <?php if ($node->field_slideshow_entry_path) {
                 
                $path = $node->field_slideshow_entry_path[$lang][0]['value']; ?>
                <div class="views-field views-field-field-teaser-image">
                    <div class="field-content">
                    <a href="<?php print url($path); ?>"><img  src="<?php print $image; ?>" title="<?php print $title; ?>" alt="<?php print $alt; ?>"/></a>
                    </div>
                </div>
                <?php } else { ?>
                <div class="views-field views-field-field-teaser-image">
                    <div class="field-content">
                    <img  src="<?php print $image; ?>" title="<?php print $title; ?>" alt="<?php print $alt; ?>"/>
                    </div>
                </div>
                <?php } ?>
            
            <?php } ?>
            <?php if($node->field_slideshow_caption[$lang][0]["value"] == "1") { ?>
            <div class="caption-wrapper">  
                <div class="caption">
            	
				<?php $title = $node->title;  $page_title_suffix=""; if (strlen($title)>45): $page_title_suffix="..."; endif; $title = substr($title,0, 40); ?>
                <?php if ($node->field_slideshow_entry_path) { ?>
                <?php $path = $node->field_slideshow_entry_path[$lang][0]['value']; ?>
                <h1><a href="<?php print url($path); ?>"><?php print $title . $page_title_suffix; ?></a></h1>
                <?php } else { ?>
                <h1><?php print $title . $page_title_suffix; ?></h1>
                <?php } ?>
                
                <?php if ($node->field_teaser_text): ?>
                <?php $text_teaser = $node->field_teaser_text[$lang][0]['value'];  $text_teaser_suffix=""; if (strlen($text_teaser)>100): $text_teaser_suffix="..."; endif; $text_teaser = substr($text_teaser,0, 100); ?>
                <div class="hidden-sm hidden-xs text"><p><?php print $text_teaser . $text_teaser_suffix; ?></p></div>
                <?php endif; ?>

                <?php if ($node->field_slideshow_entry_path): ?>
                <?php $path = $node->field_slideshow_entry_path[$lang][0]['value']; ?>
                <a href="<?php print url($path); ?>" class="more"><?php print t('Read more'); ?></a>
                <?php endif; ?>
                
                </div>
            </div>
            <?php } ?>
            
        <?php } else { print $row; } ?> 
        
        </li>
        <?php } ?>
        </ul>
    </div>
</div> 
<?php
$effect=theme_get_setting('slideshow_effect');
$effect_time=theme_get_setting('slideshow_effect_time')*1000;

drupal_add_js('jQuery(document).ready(function($) { 

	$(window).load(function() {
        $("#slideshow .flexslider").fadeIn("slow");
		$("#slideshow .flexslider").flexslider({
		animation: "'.$effect.'",             // Select your animation type, "fade" or "slide"
		slideshowSpeed: "'.$effect_time.'",   // Set the speed of the slideshow cycling, in milliseconds
        prevText: "",           
        nextText: "",           
		pauseOnAction: false,
        useCSS: false
		});
		
	});
});',
array('type' => 'inline', 'scope' => 'header'));
	
?>