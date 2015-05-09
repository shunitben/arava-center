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

            // change attendance status
            $('.attendance-value').click(function(){
                var current = $(this).text(),
                    user_name = $(this).parents('tr').find('.student-name').text(),
                    buttons = [],
                    uid =  $(this).parents('tr').find('.student-id').text(),
                    course_id = $(this).parents('tr').find('.course-id').text(),
                    lesson_num = $(this).siblings('.lesson-num').text();

                if (current !== '0') {
                    buttons.push({
                        text: Drupal.t("Absent"),
                        click: function() {
                            Drupal.behaviors.arava_admin.changeAttendanceStatus(uid, course_id, lesson_num, 0);
                            $( this ).dialog( "close" );
                        }
                    });
                }
                if (current !== '1') {
                    buttons.push({
                        text: Drupal.t("Present"),
                        click: function() {
                            Drupal.behaviors.arava_admin.changeAttendanceStatus(uid, course_id, lesson_num, 1);
                            $( this ).dialog( "close" );
                        }
                    });
                }
                if (current !== '2') {
                    buttons.push({
                        text: Drupal.t("Made up"),
                        click: function() {
                            Drupal.behaviors.arava_admin.changeAttendanceStatus(uid, course_id, lesson_num, 2);
                            $( this ).dialog( "close" );
                        }
                    });
                }

                var choose = '<div>' + Drupal.t('What status do you want to change @name\'s status to?', {'@name': user_name}) + '</div>';
                $(choose).dialog({
                    height: 200,
                    width: 300,
                    modal: true,
                    buttons: buttons
                });
            });

            // remove from course
            $('.remove_from_course').click(function(){
                var user_name = $(this).parents('tr').find('.views-field-field-user-name').text();
                if (window.confirm(Drupal.t('Are you sure you want to remove @name from the course?', {'@name': user_name}))) {
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
                }
            });

            // uncheck all
            $('.uncheck-all').click(function(e) {
                e.preventDefault();
                $('.form-item-emails input').removeAttr('checked');
                $(this).addClass('hidden');
                $('.check-all').removeClass('hidden');
            });
            // check all
            $('.check-all').click(function(e) {
                e.preventDefault();
                $('.form-item-emails input').attr('checked', 'checked');
                $(this).addClass('hidden');
                $('.uncheck-all').removeClass('hidden');
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
        },

        changeAttendanceStatus: function(uid, course_id, lesson_num, status) {
            var square = '.attendance-' + uid + '-' + lesson_num;
            $(square).addClass('loading');
            $.ajax({url: '/admin/attendance/change-status/'+uid+'/'+course_id+'/'+lesson_num+'/'+status})
            .done(function() {
                $(square).removeClass('int-val-0');
                $(square).removeClass('int-val-1');
                $(square).removeClass('int-val-2');
                $(square).removeClass('loading');
                $(square).addClass('int-val-' + status);
                $(square).text(status);
            });
        }


    }
}(window.Drupal, window.jQuery));
