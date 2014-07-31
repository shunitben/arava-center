<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php 
  if ($node->field_mt_email){ $email = $node->field_mt_email['und'][0]['value']; }
  if ($node->field_mt_twitter){ $twitter = $node->field_mt_twitter['und'][0]['value']; }
  if ($node->field_mt_linkedin){ $linkedin = $node->field_mt_linkedin['und'][0]['value']; }
  ?>

  <div class="student-content-wrapper clearfix">
    <?php if ($photo = render($content['field_mt_photo'])) { ?>
      <div class="photo-wrapper">
        <?php print render($photo); ?>
        
        <?php if (render($content['field_mt_email']) || render($content['field_mt_twitter']) || render($content['field_mt_linkedin']) ) { ?>
              <ul class="members-social-bookmarks">
                <?php if (render($content['field_mt_email'])) { ?><li class="email"><a target="_blank" href="mailto:<?php print $email;?>"><i class="fa"></i></a></li><?php } ?>
                <?php if (render($content['field_mt_twitter'])) { ?><li class="twitter"><a target="_blank" href="http://<?php print $twitter;?>"><i class="fa fa-twitter"></i></a></li><?php } ?> 
                <?php if (render($content['field_mt_linkedin'])) { ?><li class="linkedin"><a target="_blank" href="http://<?php print $linkedin;?>"><i class="fa fa-linkedin"></i></a></li><?php } ?> 
              </ul>
        <?php } ?>
      </div>
    <?php } else { ?>
        <?php if (render($content['field_mt_email']) || render($content['field_mt_twitter']) || render($content['field_mt_linkedin']) ) { ?>
              <ul class="members-social-bookmarks">
                <?php if (render($content['field_mt_email'])) { ?><li class="email"><a target="_blank" href="mailto:<?php print $email;?>"><i class="fa"></i></a></li><?php } ?>
                <?php if (render($content['field_mt_twitter'])) { ?><li class="twitter"><a target="_blank" href="http://<?php print $twitter;?>"><i class="fa fa-twitter"></i></a></li><?php } ?> 
                <?php if (render($content['field_mt_linkedin'])) { ?><li class="linkedin"><a target="_blank" href="http://<?php print $linkedin;?>"><i class="fa fa-linkedin"></i></a></li><?php } ?> 
              </ul>
        <?php } ?>
    <?php } ?>

    <?php if ($photo = render($content['field_mt_photo'])) { ?>
    <div class="article-content custom-width">
    <?php } else { ?>
    <div class="article-content full-width">
    <?php } ?>

      <header>
        <?php print render($title_prefix); ?>
        <?php if (!$page) { ?>
          <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
        <?php } else { ?>
          <h1 class="node-title" <?php print $title_attributes; ?>><?php print $title; ?></h1>
        <?php } ?>
        <?php print render($title_suffix); ?>

        <?php if ($display_submitted): ?>
          <div class="submitted-info">
          <?php print $submitted; ?>
          </div>
        <?php endif; ?>
          
        <?php print $user_picture; ?> 
      </header>

      <div class="content"<?php print $content_attributes; ?>>
        <?php
          // We hide the comments and links now so that we can render them later.
          hide($content['comments']);
          hide($content['links']);
          hide($content['group_mt_student_details']);
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
    <?php print render($content['group_mt_student_details']); ?>
    <?php print render($content['comments']); ?>

</article>