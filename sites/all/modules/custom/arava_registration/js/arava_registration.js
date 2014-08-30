(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_registration = {
        attach: function (context) {

            $('.dialog-link').click(function(e){
                e.preventDefault();
                var id = $(this).parents('.checkbox-field-wrapper').attr('takanon-id'),
                    link = $(this).attr('href');
                Drupal.behaviors.arava_registration.showTakanon(id, link);

            });

            $('#arava-registration-extra input[type="checkbox"]').click(function(e){
                e.preventDefault();
                var id = $(this).parents('.checkbox-field-wrapper').attr('takanon-id'),
                    link = $(this).siblings('label').find('.dialog-link').attr('href');
                Drupal.behaviors.arava_registration.showTakanon(id, link);
            })

            $('#arava-registration-extra .agree').click(function() {
                var name = $(this).parent().siblings('input').val(),
                    takanon = $(this).parent().siblings('input').attr('name');
                Drupal.behaviors.arava_registration.saveAndCloseTakanon(name, takanon, $(this));
            });

            // Capture pressing of the "enter" button in this input, and "click" agree.
            $('.ui-dialog-content.takanon input').live("keypress", function(e) {
                if (e.keyCode == 13) {
                    $(this).siblings('.field-suffix').find('.agree').trigger('click');
                    return false;
                }
            });

            // time tables
            Drupal.behaviors.arava_registration.timetableNavigation();

            // course validation - collisions and ajax timetable
            Drupal.behaviors.arava_registration.collectSelectedCourses();
            $('.view-course-selection input[type="checkbox"]').click(function(e) {
                var action,
                    course_id,
                    times = $(this).parent().siblings('.views-row').find('.lesson-times').text();
                times = JSON.parse(times);
                course_id = times[0].course_id;

                // collisions
                if (!$(this).is(':checked')) {
                    action = 'remove';
                    Drupal.behaviors.arava_registration.removeFromSelectedCourses(times);
                }
                else {
                    action = 'add';
                    var valid = Drupal.behaviors.arava_registration.validateCoursesCollision(times);
                    if (valid !== false) {
                        e.preventDefault();
                        var error = '<div>' + Drupal.t('You cannot choose this course - it clashes with ') + valid.old_course + '</div>';
                        $(error).dialog({
                           height: 200,
                           width: 300,
                           modal: true
                        });
                        return;
                    }
                }

                // ajax timetable
                var url = '/registration/course/' + course_id + '/' + action;
                $('.my-timetable-block').append('<div class="calendar-loader"></div>');
                $.ajax({url: url})
                    .done(function( data ) {
                        var response = JSON.parse(data);
                        if (response.timetable) {
                            $('.my-timetable-block').html(response.timetable);
                            // re-apply
                            Drupal.behaviors.arava_registration.timetableNavigation();
                        }
                    });
            });
        },

        showTakanon: function (id, link) {
            var selector = '.takanon[takanon-id=' + id + ']'
            $(selector).removeClass('hidden');
            $('.takanon-text', selector).load(link + ' .field-name-body');
            $(selector).dialog({
                height: 450,
                width: 600,
                modal: true,
                title: Drupal.t('Please read and sign your name at the bottom')
            });
            // keep the selector to use it for closing later
            Drupal.behaviors.arava_registration.dialog_selector = selector;
        },

        saveAndCloseTakanon: function(name, takanon, agreeButton) {
            // remove old errors
            $('.agree-error').remove();
            // check name is not empty
            if (name == '') {
                agreeButton.after('<span class="agree-error">' + Drupal.t('Please write your name.') + '</span>');
                return;
            }
            // do ajax
            agreeButton.addClass('processing');
            var url = '/registration/extra/agreed/' + name + '/' + takanon;
            $.ajax({url: url})
                .done(function( data ) {
                    var response = JSON.parse(data);
                    if (response.success) {
                        // close the dialog and check the checkbox
                        $(Drupal.behaviors.arava_registration.dialog_selector).dialog("close");
                        $('input[name=' + takanon + '_checkbox]').attr('checked', 'checked').attr('disabled', 'disabled');
                        agreeButton.removeClass('processing');
                    }
                    else {
                        // display error as relevant
                        if (response.error !== 'undefined') {
                            var error = response.error;
                        }
                        else {
                            var error = Drupal.t('There\'s been an error saving your agreement. Please try clicking again.')
                        }
                        agreeButton.removeClass('processing');
                        agreeButton.after('<span class="agree-error">' + error + '</span>');
                    }
                });
        },

        timetableNavigation: function() {
            var timetableBlock = $('.my-timetable-block'),
                timetables = $('.view-calendar', timetableBlock),
                prevLinks = $('.date-prev', timetables),
                nextLinks = $('.date-next', timetables),
                numMonths = timetables.length,
                currentMonth = 1;

            $('a', prevLinks).eq(0).attr('disabled', 'disabled');
            $('a', nextLinks).eq(numMonths - 1).attr('disabled', 'disabled');

            nextLinks.click(function(e){
                e.preventDefault();
                if (currentMonth < numMonths) {
                    timetables.eq(currentMonth - 1).hide();
                    timetables.eq(currentMonth).show();
                    currentMonth = currentMonth + 1;
                }
            });

            prevLinks.click(function(e){
                e.preventDefault();
                if (currentMonth > 1) {
                    timetables.eq(currentMonth - 1).hide();
                    timetables.eq(currentMonth - 2).show();
                    currentMonth = currentMonth - 1;
                }
            });

            // color the lessons
            var colors = ['#B6E9FA', '#FAE0B6', '#B6D0FA','#BCB6FA','#FAE0B6','#DFB6FA','#F1FAB6','#FAB6F1','#C8FAB6','#FAB6BF','#B6FADB','#FACBB6', '#B6FAEE'],
                color_index = 0,
                map = [];
            $('.colored-item').each(function(){
                var course_id = $(this).attr('course');
                if (!map[course_id]) {
                    map[course_id] = colors[color_index];
                    color_index++;
                }
                $(this).parents('.monthview').css({'background-color' : map[course_id]});
            });
        },

        collectSelectedCourses: function() {
            var allTimes = [];
            $('.view-course-selection input[type="checkbox"]').filter(':checked').each(function(i){
                var courseTimes = $(this).parent().siblings('.views-row').find('.lesson-times').text();
                courseTimes = JSON.parse(courseTimes);
                allTimes = allTimes.concat(courseTimes);
            });
            Drupal.behaviors.arava_registration.selectedCoursesTimes = allTimes;
        },

        validateCoursesCollision: function(courseTimes) {
            var allTimes = Drupal.behaviors.arava_registration.selectedCoursesTimes;

            var i,j;
            for (i=0; i < courseTimes.length; i++) {
                for (j=0; j < allTimes.length; j++) {
                    // check collision
                    if ((courseTimes[i]['start'] >= allTimes[j]['start'] && courseTimes[i]['start'] < allTimes[j]['end'])
                        || (courseTimes[i]['end'] > allTimes[j]['start'] && courseTimes[i]['end'] <= allTimes[j]['end'])) {
                        return {new_course: courseTimes[i]['course_name'], old_course: allTimes[j]['course_name']};
                    }
                }
                // add to allTimes
                allTimes.push(courseTimes[i]);
            }
            // if we haven't returned yet, let's update allTimes
            Drupal.behaviors.arava_registration.selectedCoursesTimes = allTimes;
            return false;
        },

        removeFromSelectedCourses: function(courseTimes) {
            var allTimes = Drupal.behaviors.arava_registration.selectedCoursesTimes;
            var removeKey = courseTimes[0]['course_id'],
                rebuildAllTimes = [];

            for (var key in allTimes) {
                if (allTimes[key]['course_id'] != removeKey) {
                    rebuildAllTimes.push(allTimes[key]);
                }
            }
            Drupal.behaviors.arava_registration.selectedCoursesTimes = rebuildAllTimes;
        }

    }
}(window.Drupal, window.jQuery));
