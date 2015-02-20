(function (Drupal, $) {
    'use strict';

    Drupal.behaviors.arava_assignments = {
        attach: function (context) {
// working very badly!
//            $('#edit-checker').chosen();

            $('#arava-assignments-do-assignment-form #edit-submit-done').click(function(e) {
                var confirmationText = Drupal.t("By clicking this button, you are saying that you completed all the assignments needed to enter the next lesson.");
                confirmationText += "\n";
                confirmationText += Drupal.t("This includes answering the questions, and for homework assignments, it also includes meditations and sometimes debates.");
                confirmationText += "\n\n";
                confirmationText += Drupal.t( "Do you confirm that this is what you meant to do?");

                if (!window.confirm(confirmationText)) {
                    e.preventDefault();
                }
            })

        }



    }
}(window.Drupal, window.jQuery));
