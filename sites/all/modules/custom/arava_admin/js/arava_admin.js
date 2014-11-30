(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_admin = {
        attach: function (context) {

            // @todo: color all unchecked in attendance red

            $('.page-admin-attendance-take .form-type-checkboxes input[type=checkbox]').click(function(){
                if ($(this).is(':checked')) {
                    $(this).parent().siblings().find('input[type=checkbox]').removeAttr('checked');
                }
                //@todo: color it red if unchecked
            })

        }


    }
}(window.Drupal, window.jQuery));
