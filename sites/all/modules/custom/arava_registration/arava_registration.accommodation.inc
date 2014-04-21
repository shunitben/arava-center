<?php

/**
 * Page callback for accommodation
 */
function arava_registration_accommodation($form, &$form_state) {


}

/**
 * Accommodation selection validation function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_accommodation_validate($form, &$form_state) {

}

/**
 * Accommodation selection submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_accommodation_submit($form, &$form_state) {

	$form_state['redirect'] = array('accommodation');
}