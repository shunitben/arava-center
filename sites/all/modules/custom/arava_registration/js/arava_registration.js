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

            Drupal.behaviors.arava_registration.timetableNavigation();
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
            var url = '/registration/extra/agreed/' + name + '/' + takanon;
            $.ajax({url: url})
                .done(function( data ) {
                    var response = JSON.parse(data);
                    if (response.success) {
                        // close the dialog and check the checkbox
                        $(Drupal.behaviors.arava_registration.dialog_selector).dialog("close");
                        $('input[name=' + takanon + '_checkbox]').attr('checked', 'checked').attr('disabled', 'disabled');
                    }
                    else {
                        // display error as relevant
                        if (response.error !== 'undefined') {
                            var error = response.error;
                        }
                        else {
                            var error = Drupal.t('There\'s been an error saving your agreement. Please try clicking again.')
                        }
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
        }

    }
}(window.Drupal, window.jQuery));
