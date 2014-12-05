(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_admin = {
        attach: function (context) {

            // disable attendance form when changing lesson selection
            $('#arava-admin-attendance-choose-lesson-form select').change(function() {
                $('.attendance_warning').show();
            });
            $('.discard_attendance_warning').click(function() {
                $('.attendance_warning').hide();
            });

            Drupal.behaviors.arava_admin.colorUncheckedRed();

            $('.page-admin-attendance-take .form-type-checkboxes input[type=checkbox]').click(function(){
                if ($(this).is(':checked')) {
                    $(this).parent().siblings().find('input[type=checkbox]').removeAttr('checked');
                }
                Drupal.behaviors.arava_admin.colorUncheckedRed();
            })

        },

        colorUncheckedRed: function() {
            $('#edit-attendance .form-type-checkboxes').each(function() {
                if ($(this).find('input[type=checkbox]:checked').length == 0) {
                    $(this).find('label').addClass('absent');
                }
                else {
                    $(this).find('label').removeClass('absent');
                }
            })
        }


    }
}(window.Drupal, window.jQuery));
