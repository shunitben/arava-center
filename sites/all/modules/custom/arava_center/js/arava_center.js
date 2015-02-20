(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_center = {
        attach: function (context) {
//            $('.view-animals .view-content').accordion({
//                collapsible: true,
//                heightStyle: "content",
//                active:false
//            });

            $('.view-animals .view-grouping-content').hide();
            $('.view-animals .view-grouping-header').prepend('<span class="toggle plus">+</span> ');

            $('.view-animals .view-grouping-header').click(function(){
                var sibling = $(this).siblings('.view-grouping-content');
                sibling.toggle();

                $('.view-animals .view-grouping-content').not(sibling).hide();
            });
        }

    }
}(window.Drupal, window.jQuery));
