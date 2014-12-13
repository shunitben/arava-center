(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_admin = {
        attach: function (context) {

            // disable attendance form when changing lesson selection
            $('.page-admin-attendance-take select').change(function() {
                $('.attendance_warning').show();
            });
            $('.discard_attendance_warning').click(function() {
                $('.attendance_warning').hide();
            });

            // confirm before leaving the page with unsaved changes
            $('.page-admin-attendance-take #form-div .form-submit').click(function(e) {
                if (Drupal.behaviors.arava_admin.hasChanges) {
                    var message = Drupal.t("You are about to leave this attendance form without saving your changes.\n" +
                        "If that is what you want to do, click 'OK'.\n" +
                        "Otherwise click 'cancel' to close this warning and then save your changes at the bottom of the page."),
                        confirm = window.confirm(message);
                    if (confirm == false) {
                        $('.attendance_warning').hide();
                        e.preventDefault();
                    }
                }
            })

            Drupal.behaviors.arava_admin.colorUncheckedRed();

            $('.page-admin-attendance-take .form-type-checkboxes input[type=checkbox]').click(function(){
                Drupal.behaviors.arava_admin.hasChanges = true;
                if ($(this).is(':checked')) {
                    $(this).parent().siblings().find('input[type=checkbox]').removeAttr('checked');
                }
                Drupal.behaviors.arava_admin.colorUncheckedRed();
            })

            // remove from course
            $('.remove_from_course').click(function(){
               var course = $(this).attr('course'),
                   user = $(this).attr('user'),
                   this_row = $(this).parents('tr');
               if (!isNaN(course) && !isNaN(user)) {
                   $(this).addClass('loading');
                    $.ajax({url: '/admin/course/' + course + '/remove/' + user})
                    .done(function( data ) {
                        var response = JSON.parse(data);
                        if (response.success) {
                            this_row.remove();
                        }
                    });
               }
            });

        },

        hasChanges: false,

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
