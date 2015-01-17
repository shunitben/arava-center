<?php
/**
 * @file
 * arava_registration_wizard.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function arava_registration_wizard_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'accommodation_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Accommodation list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'חדרי האירוח';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accomodation' => 'accomodation',
  );
  /* Filter criterion: Content: Nid */
  $handler->display->display_options['filters']['nid']['id'] = 'nid';
  $handler->display->display_options['filters']['nid']['table'] = 'node';
  $handler->display->display_options['filters']['nid']['field'] = 'nid';
  $handler->display->display_options['filters']['nid']['operator'] = '!=';
  $handler->display->display_options['filters']['nid']['value']['value'] = '10';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'accommodation';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'חדרים 2';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $translatables['accommodation_list'] = array(
    t('Master'),
    t('חדרי האירוח'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Page'),
  );
  $export['accommodation_list'] = $view;

  $view = new view();
  $view->name = 'accomodation_selection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Accomodation Selection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'הרשמה ללינה';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'מידע נוסף';
  /* Field: Content: Price */
  $handler->display->display_options['fields']['field_price']['id'] = 'field_price';
  $handler->display->display_options['fields']['field_price']['table'] = 'field_data_field_price';
  $handler->display->display_options['fields']['field_price']['field'] = 'field_price';
  $handler->display->display_options['fields']['field_price']['label'] = 'עלות לסמסטר';
  $handler->display->display_options['fields']['field_price']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<span class="hidden">nid:[nid]</span>';
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  /* Sort criterion: Content: Price (field_price) */
  $handler->display->display_options['sorts']['field_price_value']['id'] = 'field_price_value';
  $handler->display->display_options['sorts']['field_price_value']['table'] = 'field_data_field_price';
  $handler->display->display_options['sorts']['field_price_value']['field'] = 'field_price_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accomodation' => 'accomodation',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $translatables['accomodation_selection'] = array(
    t('Master'),
    t('הרשמה ללינה'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('מידע נוסף'),
    t('עלות לסמסטר'),
    t('<span class="hidden">nid:[nid]</span>'),
    t('Block'),
  );
  $export['accomodation_selection'] = $view;

  $view = new view();
  $view->name = 'calendar';
  $view->description = '';
  $view->tag = 'Calendar';
  $view->base_table = 'node';
  $view->human_name = 'Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['id'] = 'reverse_field_course_field_collection_item';
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['field'] = 'reverse_field_course_field_collection_item';
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['label'] = 'my course field collection';
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['required'] = TRUE;
  /* Relationship: Field collection item: Entity with the My Courses (field_my_courses) */
  $handler->display->display_options['relationships']['field_my_courses_node']['id'] = 'field_my_courses_node';
  $handler->display->display_options['relationships']['field_my_courses_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_my_courses_node']['field'] = 'field_my_courses_node';
  $handler->display->display_options['relationships']['field_my_courses_node']['relationship'] = 'reverse_field_course_field_collection_item';
  $handler->display->display_options['relationships']['field_my_courses_node']['label'] = 'my semester';
  $handler->display->display_options['relationships']['field_my_courses_node']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['relationship'] = 'field_my_courses_node';
  $handler->display->display_options['relationships']['field_semester_target_id']['label'] = 'semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['required'] = TRUE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['title']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '12';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['title_1']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title_1']['alter']['max_length'] = '12';
  $handler->display->display_options['fields']['title_1']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Content: Lesson times */
  $handler->display->display_options['fields']['field_lesson_times']['id'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['table'] = 'field_data_field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['field'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['label'] = '';
  $handler->display->display_options['fields']['field_lesson_times']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_lesson_times']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_lesson_times']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="colored-item" course="[nid]">
  <div class="title">[title_1]</div>
  <div class="hours">[field_lesson_times]</div>
<div class="calendar-popup">
 <div class="title">[title]</div>
  <div class="hours">[field_lesson_times]</div>
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Lesson times -  start date (field_lesson_times) */
  $handler->display->display_options['sorts']['field_lesson_times_value']['id'] = 'field_lesson_times_value';
  $handler->display->display_options['sorts']['field_lesson_times_value']['table'] = 'field_data_field_lesson_times';
  $handler->display->display_options['sorts']['field_lesson_times_value']['field'] = 'field_lesson_times_value';
  /* Filter criterion: Content: Open for registration (field_open_for_registration) */
  $handler->display->display_options['filters']['field_open_for_registration_value']['id'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['table'] = 'field_data_field_open_for_registration';
  $handler->display->display_options['filters']['field_open_for_registration_value']['field'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['relationship'] = 'field_semester_target_id';
  $handler->display->display_options['filters']['field_open_for_registration_value']['value'] = array(
    1 => '1',
  );

  /* Display: Month */
  $handler = $view->new_display('page', 'Month', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_lesson_times.field_lesson_times_value' => 'field_data_field_lesson_times.field_lesson_times_value',
  );
  /* Contextual filter: Content: User (field_user) */
  $handler->display->display_options['arguments']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['arguments']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['arguments']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['arguments']['field_user_target_id']['relationship'] = 'field_my_courses_node';
  $handler->display->display_options['arguments']['field_user_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_user_target_id']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['field_user_target_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_user_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_user_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_user_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'semester-lessons';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Month';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Calendar';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Week */
  $handler = $view->new_display('page', 'Week', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'week';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'week';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_lesson_times.field_lesson_times_value' => 'field_data_field_lesson_times.field_lesson_times_value',
  );
  $handler->display->display_options['path'] = 'calendar-node-field-lesson-times/week';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Week';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Day */
  $handler = $view->new_display('page', 'Day', 'page_3');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'day';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'day';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_lesson_times.field_lesson_times_value' => 'field_data_field_lesson_times.field_lesson_times_value',
  );
  $handler->display->display_options['path'] = 'calendar-node-field-lesson-times/day';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Day';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Year */
  $handler = $view->new_display('page', 'Year', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'year';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'year';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Content: Lesson times */
  $handler->display->display_options['fields']['field_lesson_times']['id'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['table'] = 'field_data_field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['field'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['label'] = '';
  $handler->display->display_options['fields']['field_lesson_times']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_lesson_times']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_lesson_times.field_lesson_times_value' => 'field_data_field_lesson_times.field_lesson_times_value',
  );
  $handler->display->display_options['path'] = 'calendar-node-field-lesson-times/year';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Year';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'mini';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '1';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_lesson_times.field_lesson_times_value' => 'field_data_field_lesson_times.field_lesson_times_value',
  );

  /* Display: Upcoming */
  $handler = $view->new_display('block', 'Upcoming', 'block_2');
  $handler->display->display_options['display_description'] = 'Upcoming events block';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_lesson_times.field_lesson_times_value' => 'field_data_field_lesson_times.field_lesson_times_value',
  );

  /* Display: Catalog */
  $handler = $view->new_display('page', 'Catalog', 'page_4');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['title']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '12';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['title_1']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title_1']['alter']['max_length'] = '12';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Content: Lesson times */
  $handler->display->display_options['fields']['field_lesson_times']['id'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['table'] = 'field_data_field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['field'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['label'] = '';
  $handler->display->display_options['fields']['field_lesson_times']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_lesson_times']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['settings'] = array(
    'format_type' => 'hour',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_lesson_times']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="colored-item" course="[nid]">
  <div class="title">[title_1]</div>
  <div class="hours">[field_lesson_times]</div>
<div class="calendar-popup">
 <div class="title">[title]</div>
  <div class="hours">[field_lesson_times]</div>
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_lesson_times.field_lesson_times_value' => 'field_data_field_lesson_times.field_lesson_times_value',
  );
  $handler->display->display_options['path'] = 'catalog-calendar';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Month';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Calendar';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['calendar'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('my course field collection'),
    t('my semester'),
    t('semester'),
    t('<div class="colored-item" course="[nid]">
  <div class="title">[title_1]</div>
  <div class="hours">[field_lesson_times]</div>
<div class="calendar-popup">
 <div class="title">[title]</div>
  <div class="hours">[field_lesson_times]</div>
</div>
</div>'),
    t('Month'),
    t('הכל'),
    t('Week'),
    t('Day'),
    t('Year'),
    t('Block'),
    t('Upcoming'),
    t('Upcoming events block'),
    t('Catalog'),
    t('Content entity referenced from field_semester'),
  );
  $export['calendar'] = $view;

  $view = new view();
  $view->name = 'catalog';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Catalog';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Catalog';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1000';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'term_node_tid',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: פקולטה (field_faculty) */
  $handler->display->display_options['relationships']['field_faculty_tid']['id'] = 'field_faculty_tid';
  $handler->display->display_options['relationships']['field_faculty_tid']['table'] = 'field_data_field_faculty';
  $handler->display->display_options['relationships']['field_faculty_tid']['field'] = 'field_faculty_tid';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['label'] = 'semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['required'] = TRUE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['relationship'] = 'field_faculty_tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_type'] = '0';
  $handler->display->display_options['fields']['tid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['tid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: All taxonomy terms */
  $handler->display->display_options['fields']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['fields']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['fields']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['fields']['term_node_tid']['label'] = '';
  $handler->display->display_options['fields']['term_node_tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['term_node_tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['term_node_tid']['link_to_taxonomy'] = FALSE;
  $handler->display->display_options['fields']['term_node_tid']['vocabularies'] = array(
    'faculties' => 0,
    'tags' => 0,
  );
  /* Field: Content: ימי השיעור */
  $handler->display->display_options['fields']['field_lesson_days']['id'] = 'field_lesson_days';
  $handler->display->display_options['fields']['field_lesson_days']['table'] = 'field_data_field_lesson_days';
  $handler->display->display_options['fields']['field_lesson_days']['field'] = 'field_lesson_days';
  $handler->display->display_options['fields']['field_lesson_days']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '1000',
  );
  /* Field: Content: מורה */
  $handler->display->display_options['fields']['field_teacher']['id'] = 'field_teacher';
  $handler->display->display_options['fields']['field_teacher']['table'] = 'field_data_field_teacher';
  $handler->display->display_options['fields']['field_teacher']['field'] = 'field_teacher';
  $handler->display->display_options['fields']['field_teacher']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_teacher']['settings'] = array(
    'view_mode' => 'default',
    'links' => 0,
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<span tid="[tid]" class="catalog-weight-span" nid="[nid]"></span>';
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Sort criterion: Field: Weight (field_weight) */
  $handler->display->display_options['sorts']['field_weight_value_1']['id'] = 'field_weight_value_1';
  $handler->display->display_options['sorts']['field_weight_value_1']['table'] = 'field_data_field_weight';
  $handler->display->display_options['sorts']['field_weight_value_1']['field'] = 'field_weight_value';
  $handler->display->display_options['sorts']['field_weight_value_1']['relationship'] = 'field_faculty_tid';
  /* Sort criterion: Field: Weight (field_weight) */
  $handler->display->display_options['sorts']['field_weight_value']['id'] = 'field_weight_value';
  $handler->display->display_options['sorts']['field_weight_value']['table'] = 'field_data_field_weight';
  $handler->display->display_options['sorts']['field_weight_value']['field'] = 'field_weight_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'course' => 'course',
  );
  /* Filter criterion: Content: Open for registration (field_open_for_registration) */
  $handler->display->display_options['filters']['field_open_for_registration_value']['id'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['table'] = 'field_data_field_open_for_registration';
  $handler->display->display_options['filters']['field_open_for_registration_value']['field'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['relationship'] = 'field_semester_target_id';
  $handler->display->display_options['filters']['field_open_for_registration_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Content: הסתרה בקטלוג (field_hide_from_catalog) */
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['id'] = 'field_hide_from_catalog_value';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['table'] = 'field_data_field_hide_from_catalog';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['field'] = 'field_hide_from_catalog_value';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['value'] = array(
    1 => '1',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'catalog';
  $translatables['catalog'] = array(
    t('Master'),
    t('Catalog'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('term from field_faculty'),
    t('semester'),
    t('.'),
    t('ימי השיעור'),
    t('מורה'),
    t('<span tid="[tid]" class="catalog-weight-span" nid="[nid]"></span>'),
    t('Page'),
  );
  $export['catalog'] = $view;

  $view = new view();
  $view->name = 'course_selection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Course Selection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'הרשמה לקורסים';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_faculty',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['label'] = 'semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['required'] = TRUE;
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'faculty';
  $handler->display->display_options['relationships']['term_node_tid']['required'] = TRUE;
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'faculties' => 'faculties',
  );
  /* Relationship: Content: פקולטה (field_faculty) */
  $handler->display->display_options['relationships']['field_faculty_tid']['id'] = 'field_faculty_tid';
  $handler->display->display_options['relationships']['field_faculty_tid']['table'] = 'field_data_field_faculty';
  $handler->display->display_options['relationships']['field_faculty_tid']['field'] = 'field_faculty_tid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'מידע נוסף';
  /* Field: Content: מורה */
  $handler->display->display_options['fields']['field_teacher']['id'] = 'field_teacher';
  $handler->display->display_options['fields']['field_teacher']['table'] = 'field_data_field_teacher';
  $handler->display->display_options['fields']['field_teacher']['field'] = 'field_teacher';
  $handler->display->display_options['fields']['field_teacher']['label'] = 'מרצה';
  $handler->display->display_options['fields']['field_teacher']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_teacher']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_teacher']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<span class="hidden">nid:[nid]</span>';
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  /* Field: Content: פקולטה */
  $handler->display->display_options['fields']['field_faculty']['id'] = 'field_faculty';
  $handler->display->display_options['fields']['field_faculty']['table'] = 'field_data_field_faculty';
  $handler->display->display_options['fields']['field_faculty']['field'] = 'field_faculty';
  $handler->display->display_options['fields']['field_faculty']['label'] = '';
  $handler->display->display_options['fields']['field_faculty']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_faculty']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Lesson times */
  $handler->display->display_options['fields']['field_lesson_times']['id'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['table'] = 'field_data_field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['field'] = 'field_lesson_times';
  $handler->display->display_options['fields']['field_lesson_times']['label'] = '';
  $handler->display->display_options['fields']['field_lesson_times']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_lesson_times']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_times']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_lesson_times']['delta_offset'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_class'] = 'lesson-times';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
_arava_registration_print_lesson_times($data);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Field: Weight (field_weight) */
  $handler->display->display_options['sorts']['field_weight_value']['id'] = 'field_weight_value';
  $handler->display->display_options['sorts']['field_weight_value']['table'] = 'field_data_field_weight';
  $handler->display->display_options['sorts']['field_weight_value']['field'] = 'field_weight_value';
  $handler->display->display_options['sorts']['field_weight_value']['relationship'] = 'field_faculty_tid';
  /* Sort criterion: Field: Weight (field_weight) */
  $handler->display->display_options['sorts']['field_weight_value_1']['id'] = 'field_weight_value_1';
  $handler->display->display_options['sorts']['field_weight_value_1']['table'] = 'field_data_field_weight';
  $handler->display->display_options['sorts']['field_weight_value_1']['field'] = 'field_weight_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'course' => 'course',
  );
  /* Filter criterion: Content: Open for registration (field_open_for_registration) */
  $handler->display->display_options['filters']['field_open_for_registration_value']['id'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['table'] = 'field_data_field_open_for_registration';
  $handler->display->display_options['filters']['field_open_for_registration_value']['field'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['relationship'] = 'field_semester_target_id';
  $handler->display->display_options['filters']['field_open_for_registration_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Content: הסתרה בקטלוג (field_hide_from_catalog) */
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['id'] = 'field_hide_from_catalog_value';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['table'] = 'field_data_field_hide_from_catalog';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['field'] = 'field_hide_from_catalog_value';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['value'] = array(
    1 => '1',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $translatables['course_selection'] = array(
    t('Master'),
    t('הרשמה לקורסים'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('semester'),
    t('faculty'),
    t('term from field_faculty'),
    t('מידע נוסף'),
    t('מרצה'),
    t('<span class="hidden">nid:[nid]</span>'),
    t('Block'),
  );
  $export['course_selection'] = $view;

  $view = new view();
  $view->name = 'registration_summary';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'registration_summary';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'registration_summary';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['label'] = 'semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['required'] = TRUE;
  /* Relationship: Content: My Courses (field_my_courses) */
  $handler->display->display_options['relationships']['field_my_courses_value']['id'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_my_courses_value']['table'] = 'field_data_field_my_courses';
  $handler->display->display_options['relationships']['field_my_courses_value']['field'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_my_courses_value']['label'] = 'my_courses';
  $handler->display->display_options['relationships']['field_my_courses_value']['delta'] = '-1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_semester_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'סמסטר';
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Content: My Accomodation */
  $handler->display->display_options['fields']['field_my_accomodation']['id'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['field'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['label'] = 'סוג לינה';
  $handler->display->display_options['fields']['field_my_accomodation']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: My Courses */
  $handler->display->display_options['fields']['field_my_courses']['id'] = 'field_my_courses';
  $handler->display->display_options['fields']['field_my_courses']['table'] = 'field_data_field_my_courses';
  $handler->display->display_options['fields']['field_my_courses']['field'] = 'field_my_courses';
  $handler->display->display_options['fields']['field_my_courses']['label'] = 'קורסים';
  $handler->display->display_options['fields']['field_my_courses']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_my_courses']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_my_courses']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_my_courses']['multi_type'] = 'ul';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: User (field_user) */
  $handler->display->display_options['arguments']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['arguments']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['arguments']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['arguments']['field_user_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_user_target_id']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['field_user_target_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_user_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_user_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_user_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  /* Filter criterion: Content: Open for registration (field_open_for_registration) */
  $handler->display->display_options['filters']['field_open_for_registration_value']['id'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['table'] = 'field_data_field_open_for_registration';
  $handler->display->display_options['filters']['field_open_for_registration_value']['field'] = 'field_open_for_registration_value';
  $handler->display->display_options['filters']['field_open_for_registration_value']['relationship'] = 'field_semester_target_id';
  $handler->display->display_options['filters']['field_open_for_registration_value']['value'] = array(
    1 => '1',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['registration_summary'] = array(
    t('Master'),
    t('registration_summary'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('semester'),
    t('my_courses'),
    t('סמסטר'),
    t('סוג לינה'),
    t('קורסים'),
    t('הכל'),
    t('Block'),
  );
  $export['registration_summary'] = $view;

  return $export;
}
