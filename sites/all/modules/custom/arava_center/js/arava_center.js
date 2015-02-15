(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_center = {
        attach: function (context) {
            $('.view-animals .view-content').accordion({
                collapsible: true,
                heightStyle: "content",
                active:false
            });
        }

    }
}(window.Drupal, window.jQuery));
