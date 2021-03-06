(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_registration = {
        attach: function (context) {

            // only attach behaviors once on page load
            if (context == document) {
                // Show more info about the course in a dialog
                $('.view-course-selection .views-field-view-node a, .view-course-selection .views-field-title a').click(function(e) {
                    e.preventDefault();
                    var link = $(this).attr('href');
                    Drupal.behaviors.arava_registration.showCourseInfo(link);
                });

                // courses accordion
                if ($('.all-courses').length > 0) {
                    $('.all-courses').accordion({
                        collapsible: true,
                        heightStyle: "content",
                        active:false
                    });
                }
            }

            $('.dialog-link').click(function(e){
                e.preventDefault();
                var id = $(this).parents('.checkbox-field-wrapper').attr('takanon-id'),
                    link = $(this).attr('href');
                Drupal.behaviors.arava_registration.showTakanon(id, link);

            });

            $('#arava-registration-extra input[type="checkbox"]').not('#edit-no-printed-materials').click(function(e){
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

            // close dialog after health form. We might need to make this more general at some point
            if ($('.close_dialog').length > 0) {
                $('input[name=health_declaration_checkbox]', parent.document).attr('checked', 'checked').attr('disabled', 'disabled');
                $('.ui-dialog-titlebar-close', parent.document).trigger('click');
            }

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
            
            if($(".page-registration-extra")!= null){
                $(".agree").addClass("btn").addClass("btn-primary");
                $(".form-item-takanon-moa").addClass("form-group").parent().addClass("form-inline");
                $("#edit-takanon-moa").addClass("form-control");
            }

            // disable and show spinner when submitting registration pages
            $("#edit-submit").click(function() {
                $(this).addClass('processing');
            });

            if (typeof $.fn.timepicker != "undefined") {
                $('#edit-arrival-time, #edit-departure-time').timepicker({ 'timeFormat': 'H:i', 'scrollDefault': '12:00' });
            }
        },

        showCourseInfo: function (link) {
            $('body').append('<div class="course-loaded-info loading"></div>')
            $('.course-loaded-info').load(link + ' #main', function(){
                $('.course-loaded-info').removeClass('loading');
            });
            $('.course-loaded-info').dialog({
                height: 450,
                width: 600,
                modal: true,
                close: function() {$(this).dialog('destroy').remove()}
            });
        },

        showTakanon: function (id, link) {

            if (id == 'health') {
                Drupal.behaviors.arava_registration.showTakanonIframe(id, link);
                return;
            }

            var selector = '.takanon[takanon-id=' + id + ']';
            $(selector).removeClass('hidden');
            $('.takanon-text', selector).addClass('loading');
            $('.takanon-text', selector).load(link + ' .field-name-body', function(){
                $('.takanon-text', selector).removeClass('loading');
            });
            $(selector).dialog({
                height: 450,
                width: 600,
                modal: true,
                title: Drupal.t('Please read and sign your name at the bottom')
            });
            // keep the selector to use it for closing later
            Drupal.behaviors.arava_registration.dialog_selector = selector;
        },

        showTakanonIframe: function(id, link) {
            var selector = '<iframe src="' + link + '" width="564" height="350"></iframe>'
            $(selector).dialog({
                height: 450,
                width: 600,
                modal: true,
                title: Drupal.t('Please fill out this form')
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
            var url = '/registration/extra/agreed',
                data = {name: name, takanon: takanon}
            $.ajax({
                url: url,
                data: data,
                type: 'POST'
            })
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
            var timetableBlock = $('.my-timetable-block, .page-semester-timetable #block-system-main'),
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
                num_colors = colors.length,
                map = [];
            $('.colored-item').each(function(){
                var course_id = $(this).attr('course');
                if (!map[course_id]) {
                    if (color_index == num_colors) {
                        color_index = 0;
                    }
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
