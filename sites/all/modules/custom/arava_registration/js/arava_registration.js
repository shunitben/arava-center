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
        }

    }
}(window.Drupal, window.jQuery));
