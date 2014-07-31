<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php 
    if ($node->field_mt_event_date){
    $event_start_date_field = ($node->field_mt_event_date['und'][0]['value']);
    $event_start =  date_parse_from_format("Y-m-d H:i:s", "$event_start_date_field");
    $event_start_timestamp = mktime($event_start['hour'],$event_start['minute'],$event_start['second'],$event_start['month'],$event_start['day'],$event_start['year']);
    $event_start_month = format_date($event_start_timestamp, 'custom', 'M');
    $event_start_day = format_date($event_start_timestamp, 'custom', 'd');
    $event_start_h = format_date($event_start_timestamp, 'custom', 'H');
    $event_start_m = format_date($event_start_timestamp, 'custom', 'i');
    $event_end_date_field = ($node->field_mt_event_date['und'][0]['value2']);
    $event_end =  date_parse_from_format("Y-m-d H:i:s", "$event_end_date_field");
    $event_end_timestamp = mktime($event_end['hour'],$event_end['minute'],$event_end['second'],$event_end['month'],$event_end['day'],$event_end['year']);
    $event_end_month = format_date($event_end_timestamp, 'custom', 'M');
    $event_end_day = format_date($event_end_timestamp, 'custom', 'd');    
    $event_end_h = format_date($event_end_timestamp, 'custom', 'H');
    $event_end_m = format_date($event_end_timestamp, 'custom', 'i');
    }
    if ($node->field_mt_event_location) {
    $event_place = ($node->field_mt_event_location['und'][0]['value']);
    }
    ?>
    <div class="event-content-wrapper clearfix">
      <?php if($node->field_mt_event_date || $node->field_mt_event_location || ($node->field_mt_event_longitude && $node->field_mt_event_latitude)) { ?>
      <div class="event-info">
        <?php if($node->field_mt_event_date) { ?>
        <div class="event-date-wrapper">  
          <div class="event-date">
            <div class="month"><?php print $event_start_month;?></div>
            <div class="day"><?php print $event_start_day;?></div>
          </div>
        </div>
        <div class="event-duration">
          <i class="fa fa-clock-o"></i>
          <?php print $event_start_month; ?>/<?php print $event_start_day; ?> <?php print $event_start_h ?>:<?php print $event_start_m ?>
          <?php if ($event_start_timestamp != $event_end_timestamp ) { ?> - <?php print $event_end_month; ?>/<?php print $event_end_day; ?> <?php print $event_end_h; ?>:<?php print $event_end_m; } ?>
        </div>
        <?php } ?>
        <?php if ($node->field_mt_event_location) { ?>
        <div class="event-place">
          <i class="fa fa-map-marker"></i>
          <?php print $event_place ?>
        </div>
        <?php } ?>
        <?php if($node->field_mt_event_longitude && $node->field_mt_event_latitude) { ?>
          <div id="event-map"></div>
        <?php } ?>
      </div>
      <?php }?>

    <?php if($node->field_mt_event_date || $node->field_mt_event_location) { ?>
    <div class="event-content custom-width">
    <?php } else { ?>
    <div class="event-content full-width">
    <?php } ?>
      <?php if ($title_prefix || $title_suffix || $display_submitted || !$page): ?>
      <header>
        <?php print render($title_prefix); ?>
        <?php if (!$page): ?>
          <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
        <?php endif; ?>
        <?php print render($title_suffix); ?>

        <?php if ($display_submitted): ?>
          <div class="submitted-info">
          <?php print $submitted; ?>
          </div>
        <?php endif; ?>

        <?php print $user_picture; ?>

      </header>
      <?php endif; ?>

      <div class="content"<?php print $content_attributes; ?>>
        <?php
          // We hide the comments and links now so that we can render them later.
          hide($content['comments']);
          hide($content['links']);
          hide($content['group_mt_event_details']);
          print render($content);
        ?>
      </div>

      <?php if ($links = render($content['links'])): ?>
      <footer>
      <?php print render($content['links']); ?>
      </footer>
      <?php endif; ?>
    </div>
  </div>
  <?php print render($content['group_mt_event_details']); ?>
  <?php print render($content['comments']); ?>

</article>