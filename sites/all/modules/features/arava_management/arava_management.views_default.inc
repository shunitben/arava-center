<?php
/**
 * @file
 * arava_management.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function arava_management_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'admin_accommodation';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Admin Accommodation';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ניהול לינה';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view arava administration reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« לעמוד הראשון';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ לעמוד הקודם';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'לעמוד הבא ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'לעמוד האחרון »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_my_accomodation_node']['id'] = 'reverse_field_my_accomodation_node';
  $handler->display->display_options['relationships']['reverse_field_my_accomodation_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_my_accomodation_node']['field'] = 'reverse_field_my_accomodation_node';
  $handler->display->display_options['relationships']['reverse_field_my_accomodation_node']['label'] = 'my semester';
  $handler->display->display_options['relationships']['reverse_field_my_accomodation_node']['required'] = TRUE;
  /* Relationship: תוכן: מחבר */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* שדה: תוכן: כותרת */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'שם';
  /* שדה: COUNT(משתמש: Uid) */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['uid']['group_type'] = 'count';
  $handler->display->display_options['fields']['uid']['label'] = 'מספר הרשמות';
  /* שדה: תוכן: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['relationship'] = 'reverse_field_my_accomodation_node';
  $handler->display->display_options['fields']['field_semester']['label'] = '';
  $handler->display->display_options['fields']['field_semester']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_semester']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_semester']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_semester']['settings'] = array(
    'link' => 0,
  );
  /* שדה: תוכן: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'הרשמות';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/admin/arava-reports/accommodation/[nid]/[field_semester]/list">הרשמות</a>';
  $handler->display->display_options['fields']['nid']['alter']['path'] = '/admin/arava-reports/course/[nid]/list';
  /* Sort criterion: תוכן: כותרת */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accomodation' => 'accomodation',
  );
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['relationship'] = 'reverse_field_my_accomodation_node';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['relationship'] = 'reverse_field_my_accomodation_node';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/admin-accommodation';
  $translatables['admin_accommodation'] = array(
    t('Master'),
    t('ניהול לינה'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« לעמוד הראשון'),
    t('‹ לעמוד הקודם'),
    t('לעמוד הבא ›'),
    t('לעמוד האחרון »'),
    t('my semester'),
    t('author'),
    t('שם'),
    t('מספר הרשמות'),
    t('הרשמות'),
    t('<a href="/admin/arava-reports/accommodation/[nid]/[field_semester]/list">הרשמות</a>'),
    t('סמסטר'),
    t('Page'),
  );
  $export['admin_accommodation'] = $view;

  $view = new view();
  $view->name = 'admin_courses';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Admin Courses';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ניהול קורסים';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view arava administration reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« לעמוד הראשון';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ לעמוד הקודם';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'לעמוד הבא ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'לעמוד האחרון »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['id'] = 'reverse_field_course_field_collection_item';
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['field'] = 'reverse_field_course_field_collection_item';
  $handler->display->display_options['relationships']['reverse_field_course_field_collection_item']['label'] = 'my_courses';
  /* Relationship: Field collection item: Entity with the My Courses (field_my_courses) */
  $handler->display->display_options['relationships']['field_my_courses_node']['id'] = 'field_my_courses_node';
  $handler->display->display_options['relationships']['field_my_courses_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_my_courses_node']['field'] = 'field_my_courses_node';
  $handler->display->display_options['relationships']['field_my_courses_node']['relationship'] = 'reverse_field_course_field_collection_item';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['relationship'] = 'field_my_courses_node';
  $handler->display->display_options['relationships']['field_user_target_id']['label'] = 'משתמש';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['relationship'] = 'field_my_courses_node';
  $handler->display->display_options['relationships']['field_semester_target_id']['label'] = 'semester';
  /* שדה: תוכן: כותרת */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'שם';
  /* שדה: COUNT(משתמש: Uid) */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['uid']['group_type'] = 'count';
  $handler->display->display_options['fields']['uid']['label'] = 'מספר הרשמות';
  /* שדה: תוכן: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'הרשמות';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/admin/arava-reports/course/[nid]/list">הרשמות</a>';
  $handler->display->display_options['fields']['nid']['alter']['path'] = '/admin/arava-reports/course/[nid]/list';
  /* שדה: תוכן: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = 'נוכחות';
  $handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['alter']['text'] = '<a href="/admin/arava-reports/course/[nid_1]/attendance">נוכחות</a>';
  /* Sort criterion: תוכן: כותרת */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'course' => 'course',
  );
  /* Filter criterion: תוכן: כותרת */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'שם הקורס';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['relationship'] = 'field_my_courses_node';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['relationship'] = 'field_my_courses_node';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );
  /* Filter criterion: תוכן: הסתרה בקטלוג (field_hide_from_catalog) */
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['id'] = 'field_hide_from_catalog_value';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['table'] = 'field_data_field_hide_from_catalog';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['field'] = 'field_hide_from_catalog_value';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_hide_from_catalog_value']['value'] = array(
    1 => '1',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/admin-courses';
  $translatables['admin_courses'] = array(
    t('Master'),
    t('ניהול קורסים'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« לעמוד הראשון'),
    t('‹ לעמוד הקודם'),
    t('לעמוד הבא ›'),
    t('לעמוד האחרון »'),
    t('my_courses'),
    t('field_my_courses'),
    t('משתמש'),
    t('semester'),
    t('שם'),
    t('מספר הרשמות'),
    t('הרשמות'),
    t('<a href="/admin/arava-reports/course/[nid]/list">הרשמות</a>'),
    t('נוכחות'),
    t('<a href="/admin/arava-reports/course/[nid_1]/attendance">נוכחות</a>'),
    t('שם הקורס'),
    t('סמסטר'),
    t('Page'),
  );
  $export['admin_courses'] = $view;

  $view = new view();
  $view->name = 'admin_registration';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Admin Registration';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'הרשמות שלא נסתיימו';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view arava administration reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_user' => 'field_user',
    'field_user_name' => 'field_user_name',
    'edit_node' => 'edit_node',
    'field_my_courses' => 'field_my_courses',
    'field_my_accomodation' => 'field_my_accomodation',
    'field_takanon_moa' => 'field_takanon_moa',
    'field_takanon_school' => 'field_takanon_school',
    'field_health_declaration' => 'field_health_declaration',
    'field_waver' => 'field_waver',
    'field_registration_complete' => 'field_registration_complete',
    'field_payment_total' => 'field_payment_total',
    'field_payment_made' => 'field_payment_made',
    'mail' => 'mail',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_user' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_user_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_my_courses' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_my_accomodation' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_takanon_moa' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_takanon_school' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_health_declaration' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_waver' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_registration_complete' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_payment_total' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_payment_made' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* כותרת: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php
print view_get_link_to_send_emails($view);
?>';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['label'] = 'משתמש';
  $handler->display->display_options['relationships']['field_user_target_id']['required'] = TRUE;
  /* שדה: תוכן: User */
  $handler->display->display_options['fields']['field_user']['id'] = 'field_user';
  $handler->display->display_options['fields']['field_user']['table'] = 'field_data_field_user';
  $handler->display->display_options['fields']['field_user']['field'] = 'field_user';
  $handler->display->display_options['fields']['field_user']['label'] = 'תלמיד';
  $handler->display->display_options['fields']['field_user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_user']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_user']['settings'] = array(
    'link' => 1,
  );
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = 'תלמיד';
  $handler->display->display_options['fields']['field_user_name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_user_name']['alter']['path'] = '/user/[field_user]/edit';
  /* שדה: תוכן: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'עריכת הסמסטר של התלמיד';
  $handler->display->display_options['fields']['edit_node']['text'] = 'עריכת הסמסטר שלי';
  /* שדה: COUNT(תוכן: My Courses) */
  $handler->display->display_options['fields']['field_my_courses']['id'] = 'field_my_courses';
  $handler->display->display_options['fields']['field_my_courses']['table'] = 'field_data_field_my_courses';
  $handler->display->display_options['fields']['field_my_courses']['field'] = 'field_my_courses';
  $handler->display->display_options['fields']['field_my_courses']['group_type'] = 'count';
  $handler->display->display_options['fields']['field_my_courses']['label'] = 'קורסים';
  $handler->display->display_options['fields']['field_my_courses']['separator'] = ', ';
  /* שדה: תוכן: My Accomodation */
  $handler->display->display_options['fields']['field_my_accomodation']['id'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['field'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['label'] = 'לינה';
  $handler->display->display_options['fields']['field_my_accomodation']['settings'] = array(
    'link' => 0,
  );
  /* שדה: תוכן: Takanon Moa */
  $handler->display->display_options['fields']['field_takanon_moa']['id'] = 'field_takanon_moa';
  $handler->display->display_options['fields']['field_takanon_moa']['table'] = 'field_data_field_takanon_moa';
  $handler->display->display_options['fields']['field_takanon_moa']['field'] = 'field_takanon_moa';
  $handler->display->display_options['fields']['field_takanon_moa']['label'] = 'תקנון מואה';
  $handler->display->display_options['fields']['field_takanon_moa']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_takanon_moa']['alter']['text'] = '<span class="boolean-val boolean-val-[field_takanon_moa]">[field_takanon_moa]</span>';
  $handler->display->display_options['fields']['field_takanon_moa']['empty'] = '<span class="boolean-val boolean-val-0">0</span>';
  $handler->display->display_options['fields']['field_takanon_moa']['type'] = 'list_key';
  /* שדה: תוכן: Takanon School */
  $handler->display->display_options['fields']['field_takanon_school']['id'] = 'field_takanon_school';
  $handler->display->display_options['fields']['field_takanon_school']['table'] = 'field_data_field_takanon_school';
  $handler->display->display_options['fields']['field_takanon_school']['field'] = 'field_takanon_school';
  $handler->display->display_options['fields']['field_takanon_school']['label'] = 'תקנון בית הספר';
  $handler->display->display_options['fields']['field_takanon_school']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_takanon_school']['alter']['text'] = '<span class="boolean-val boolean-val-[field_takanon_school]">[field_takanon_school]</span>';
  $handler->display->display_options['fields']['field_takanon_school']['empty'] = '<span class="boolean-val boolean-val-0">0</span>';
  $handler->display->display_options['fields']['field_takanon_school']['type'] = 'list_key';
  /* שדה: תוכן: Health Declaration */
  $handler->display->display_options['fields']['field_health_declaration']['id'] = 'field_health_declaration';
  $handler->display->display_options['fields']['field_health_declaration']['table'] = 'field_data_field_health_declaration';
  $handler->display->display_options['fields']['field_health_declaration']['field'] = 'field_health_declaration';
  $handler->display->display_options['fields']['field_health_declaration']['label'] = 'הצהרת בריאות';
  $handler->display->display_options['fields']['field_health_declaration']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_health_declaration']['alter']['text'] = '<span class="boolean-val boolean-val-[field_health_declaration]">[field_health_declaration]</span>';
  $handler->display->display_options['fields']['field_health_declaration']['empty'] = '<span class="boolean-val boolean-val-0">0</span>';
  $handler->display->display_options['fields']['field_health_declaration']['type'] = 'list_key';
  /* שדה: תוכן: Waver */
  $handler->display->display_options['fields']['field_waver']['id'] = 'field_waver';
  $handler->display->display_options['fields']['field_waver']['table'] = 'field_data_field_waver';
  $handler->display->display_options['fields']['field_waver']['field'] = 'field_waver';
  $handler->display->display_options['fields']['field_waver']['label'] = 'הסרת אחריות';
  $handler->display->display_options['fields']['field_waver']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_waver']['alter']['text'] = '<span class="boolean-val boolean-val-[field_waver]">[field_waver]</span>';
  $handler->display->display_options['fields']['field_waver']['empty'] = '<span class="boolean-val boolean-val-0">0</span>';
  $handler->display->display_options['fields']['field_waver']['type'] = 'list_key';
  /* שדה: תוכן: registration complete */
  $handler->display->display_options['fields']['field_registration_complete']['id'] = 'field_registration_complete';
  $handler->display->display_options['fields']['field_registration_complete']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['fields']['field_registration_complete']['field'] = 'field_registration_complete';
  $handler->display->display_options['fields']['field_registration_complete']['label'] = 'סיום הרשמה';
  $handler->display->display_options['fields']['field_registration_complete']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_registration_complete']['alter']['text'] = '<span class="boolean-val boolean-val-[field_registration_complete]">[field_registration_complete]</span>';
  $handler->display->display_options['fields']['field_registration_complete']['empty'] = '<span class="boolean-val boolean-val-0">0</span>';
  $handler->display->display_options['fields']['field_registration_complete']['type'] = 'list_key';
  /* שדה: תוכן: Payment total */
  $handler->display->display_options['fields']['field_payment_total']['id'] = 'field_payment_total';
  $handler->display->display_options['fields']['field_payment_total']['table'] = 'field_data_field_payment_total';
  $handler->display->display_options['fields']['field_payment_total']['field'] = 'field_payment_total';
  $handler->display->display_options['fields']['field_payment_total']['label'] = 'סה״כ לתשלום';
  $handler->display->display_options['fields']['field_payment_total']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* שדה: תוכן: Payment made */
  $handler->display->display_options['fields']['field_payment_made']['id'] = 'field_payment_made';
  $handler->display->display_options['fields']['field_payment_made']['table'] = 'field_data_field_payment_made';
  $handler->display->display_options['fields']['field_payment_made']['field'] = 'field_payment_made';
  $handler->display->display_options['fields']['field_payment_made']['label'] = 'שולם';
  $handler->display->display_options['fields']['field_payment_made']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['mail']['label'] = '';
  $handler->display->display_options['fields']['mail']['exclude'] = TRUE;
  $handler->display->display_options['fields']['mail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Sort criterion: משתמש: שם מלא (field_user_name) */
  $handler->display->display_options['sorts']['field_user_name_value']['id'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['sorts']['field_user_name_value']['field'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
    2 => 'AND',
  );
  /* Filter criterion: תוכן: My Accomodation (field_my_accomodation) */
  $handler->display->display_options['filters']['field_my_accomodation_target_id']['id'] = 'field_my_accomodation_target_id';
  $handler->display->display_options['filters']['field_my_accomodation_target_id']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['filters']['field_my_accomodation_target_id']['field'] = 'field_my_accomodation_target_id';
  $handler->display->display_options['filters']['field_my_accomodation_target_id']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_my_accomodation_target_id']['group'] = 1;
  /* Filter criterion: תוכן: Takanon Moa (field_takanon_moa) */
  $handler->display->display_options['filters']['field_takanon_moa_value']['id'] = 'field_takanon_moa_value';
  $handler->display->display_options['filters']['field_takanon_moa_value']['table'] = 'field_data_field_takanon_moa';
  $handler->display->display_options['filters']['field_takanon_moa_value']['field'] = 'field_takanon_moa_value';
  $handler->display->display_options['filters']['field_takanon_moa_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_takanon_moa_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_takanon_moa_value']['group'] = 1;
  /* Filter criterion: תוכן: Takanon School (field_takanon_school) */
  $handler->display->display_options['filters']['field_takanon_school_value']['id'] = 'field_takanon_school_value';
  $handler->display->display_options['filters']['field_takanon_school_value']['table'] = 'field_data_field_takanon_school';
  $handler->display->display_options['filters']['field_takanon_school_value']['field'] = 'field_takanon_school_value';
  $handler->display->display_options['filters']['field_takanon_school_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_takanon_school_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_takanon_school_value']['group'] = 1;
  /* Filter criterion: תוכן: Health Declaration (field_health_declaration) */
  $handler->display->display_options['filters']['field_health_declaration_value']['id'] = 'field_health_declaration_value';
  $handler->display->display_options['filters']['field_health_declaration_value']['table'] = 'field_data_field_health_declaration';
  $handler->display->display_options['filters']['field_health_declaration_value']['field'] = 'field_health_declaration_value';
  $handler->display->display_options['filters']['field_health_declaration_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_health_declaration_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_health_declaration_value']['group'] = 1;
  /* Filter criterion: תוכן: Waver (field_waver) */
  $handler->display->display_options['filters']['field_waver_value']['id'] = 'field_waver_value';
  $handler->display->display_options['filters']['field_waver_value']['table'] = 'field_data_field_waver';
  $handler->display->display_options['filters']['field_waver_value']['field'] = 'field_waver_value';
  $handler->display->display_options['filters']['field_waver_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_waver_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_waver_value']['group'] = 1;
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_registration_complete_value']['group'] = 1;
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['group'] = 2;
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  $handler->display->display_options['filters']['type']['group'] = 2;

  /* Display: unfinished */
  $handler = $view->new_display('page', 'unfinished', 'page');
  $handler->display->display_options['path'] = 'admin/admin-registration/unfinished';

  /* Display: all */
  $handler = $view->new_display('page', 'all', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'כל ההרשמות';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* כותרת: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php
print view_get_link_to_send_emails($view);
?>';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );
  $handler->display->display_options['path'] = 'admin/admin-registration/all';

  /* Display: unfinished - emails */
  $handler = $view->new_display('page', 'unfinished - emails', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = '';
  $handler->display->display_options['fields']['field_user_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_user_name']['alter']['path'] = '/user/[field_user]/edit';
  $handler->display->display_options['fields']['field_user_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_user_name']['type'] = 'text_plain';
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['mail']['label'] = '';
  $handler->display->display_options['fields']['mail']['exclude'] = TRUE;
  $handler->display->display_options['fields']['mail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* שדה: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_user_name] <[mail]>;';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  $handler->display->display_options['filters']['type']['group'] = 2;
  /* Filter criterion: תוכן: Takanon Moa (field_takanon_moa) */
  $handler->display->display_options['filters']['field_takanon_moa_value']['id'] = 'field_takanon_moa_value';
  $handler->display->display_options['filters']['field_takanon_moa_value']['table'] = 'field_data_field_takanon_moa';
  $handler->display->display_options['filters']['field_takanon_moa_value']['field'] = 'field_takanon_moa_value';
  $handler->display->display_options['filters']['field_takanon_moa_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_takanon_moa_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_takanon_moa_value']['group'] = 1;
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_registration_complete_value']['group'] = 1;
  /* Filter criterion: תוכן: Health Declaration (field_health_declaration) */
  $handler->display->display_options['filters']['field_health_declaration_value']['id'] = 'field_health_declaration_value';
  $handler->display->display_options['filters']['field_health_declaration_value']['table'] = 'field_data_field_health_declaration';
  $handler->display->display_options['filters']['field_health_declaration_value']['field'] = 'field_health_declaration_value';
  $handler->display->display_options['filters']['field_health_declaration_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_health_declaration_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['path'] = 'admin/admin-registration/unfinished/emails';
  $translatables['admin_registration'] = array(
    t('Master'),
    t('הרשמות שלא נסתיימו'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('משתמש'),
    t('תלמיד'),
    t('עריכת הסמסטר של התלמיד'),
    t('עריכת הסמסטר שלי'),
    t('קורסים'),
    t('לינה'),
    t('תקנון מואה'),
    t('<span class="boolean-val boolean-val-[field_takanon_moa]">[field_takanon_moa]</span>'),
    t('<span class="boolean-val boolean-val-0">0</span>'),
    t('תקנון בית הספר'),
    t('<span class="boolean-val boolean-val-[field_takanon_school]">[field_takanon_school]</span>'),
    t('הצהרת בריאות'),
    t('<span class="boolean-val boolean-val-[field_health_declaration]">[field_health_declaration]</span>'),
    t('הסרת אחריות'),
    t('<span class="boolean-val boolean-val-[field_waver]">[field_waver]</span>'),
    t('סיום הרשמה'),
    t('<span class="boolean-val boolean-val-[field_registration_complete]">[field_registration_complete]</span>'),
    t('סה״כ לתשלום'),
    t('שולם'),
    t('סמסטר'),
    t('unfinished'),
    t('all'),
    t('כל ההרשמות'),
    t('unfinished - emails'),
    t('[field_user_name] <[mail]>;'),
  );
  $export['admin_registration'] = $view;

  $view = new view();
  $view->name = 'content_management';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Content Management';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Content Management';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« לעמוד הראשון';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ לעמוד הקודם';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'לעמוד הבא ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'לעמוד האחרון »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'type' => 'type',
    'status' => 'status',
    'changed' => 'changed',
    'edit_node' => 'edit_node',
    'delete_node' => 'delete_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* שדה: Bulk operations: תוכן */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* שדה: תוכן: כותרת */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* שדה: תוכן: סוג */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* שדה: תוכן: מפורסם */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* שדה: תוכן: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'עודכן';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* שדה: תוכן: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'עריכה';
  $handler->display->display_options['fields']['edit_node']['text'] = 'עדכן';
  /* שדה: תוכן: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = 'מחיקה';
  $handler->display->display_options['fields']['delete_node']['text'] = 'מחק';
  /* Sort criterion: תוכן: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: תוכן: מפורסם */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'מפורסם';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: תוכן: כותרת */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'כותרת';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'סוג';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content-management';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Content Management';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['content_management'] = array(
    t('Master'),
    t('Content Management'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« לעמוד הראשון'),
    t('‹ לעמוד הקודם'),
    t('לעמוד הבא ›'),
    t('לעמוד האחרון »'),
    t('- Choose an operation -'),
    t('כותרת'),
    t('סוג'),
    t('מפורסם'),
    t('עודכן'),
    t('עריכה'),
    t('עדכן'),
    t('מחיקה'),
    t('מחק'),
    t('Page'),
  );
  $export['content_management'] = $view;

  $view = new view();
  $view->name = 'courses_reports';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Courses Reports';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'נרשמים ללינה';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view arava administration reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['label'] = 'משתמש';
  $handler->display->display_options['relationships']['field_user_target_id']['required'] = TRUE;
  /* שדה: תוכן: My Accomodation */
  $handler->display->display_options['fields']['field_my_accomodation']['id'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['field'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['label'] = 'סוג לינה';
  $handler->display->display_options['fields']['field_my_accomodation']['settings'] = array(
    'link' => 0,
  );
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = 'שם';
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name_1']['id'] = 'field_user_name_1';
  $handler->display->display_options['fields']['field_user_name_1']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name_1']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name_1']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* Sort criterion: משתמש: שם מלא (field_user_name) */
  $handler->display->display_options['sorts']['field_user_name_value']['id'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['sorts']['field_user_name_value']['field'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['relationship'] = 'field_user_target_id';
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );

  /* Display: Course */
  $handler = $view->new_display('page', 'Course', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'נרשמים לקורס:';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* כותרת: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['empty'] = TRUE;
  $handler->display->display_options['header']['php']['php_output'] = '<h1><?php
print $results[0]->node_field_data_field_course_title;
?></h1>
<?php
print view_get_link_to_send_emails($view);
?>';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['label'] = 'משתמש';
  $handler->display->display_options['relationships']['field_user_target_id']['required'] = TRUE;
  /* Relationship: תוכן: My Courses (field_my_courses) */
  $handler->display->display_options['relationships']['field_my_courses_value']['id'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_my_courses_value']['table'] = 'field_data_field_my_courses';
  $handler->display->display_options['relationships']['field_my_courses_value']['field'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_my_courses_value']['label'] = 'my_courses';
  $handler->display->display_options['relationships']['field_my_courses_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_my_courses_value']['delta'] = '-1';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['relationships']['field_course_target_id']['field'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['relationship'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_course_target_id']['label'] = 'field_course';
  $handler->display->display_options['relationships']['field_course_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = 'שם';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* שדה: תוכן: כותרת */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_course_target_id';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['mail']['label'] = 'אימייל';
  /* שדה: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'מחיקה מהקורס';
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
print _arava_admin_remove_user_from_course_link($data);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: תוכן: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_course_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'admin/arava-reports/course/%/list';
  $handler->display->display_options['menu']['title'] = 'Reports - Accommodation';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Course */
  $handler = $view->new_display('page', 'Course', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'נרשמים לקורס:';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* כותרת: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['empty'] = TRUE;
  $handler->display->display_options['header']['php']['php_output'] = '<h1><?php
print $results[0]->node_field_data_field_course_title;
?></h1>';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['label'] = 'משתמש';
  $handler->display->display_options['relationships']['field_user_target_id']['required'] = TRUE;
  /* Relationship: תוכן: My Courses (field_my_courses) */
  $handler->display->display_options['relationships']['field_my_courses_value']['id'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_my_courses_value']['table'] = 'field_data_field_my_courses';
  $handler->display->display_options['relationships']['field_my_courses_value']['field'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_my_courses_value']['label'] = 'my_courses';
  $handler->display->display_options['relationships']['field_my_courses_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_my_courses_value']['delta'] = '-1';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['relationships']['field_course_target_id']['field'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['relationship'] = 'field_my_courses_value';
  $handler->display->display_options['relationships']['field_course_target_id']['label'] = 'field_course';
  $handler->display->display_options['relationships']['field_course_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = '';
  $handler->display->display_options['fields']['field_user_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_user_name']['element_label_colon'] = FALSE;
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['mail']['label'] = '';
  $handler->display->display_options['fields']['mail']['exclude'] = TRUE;
  $handler->display->display_options['fields']['mail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* שדה: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_user_name] <[mail]>;';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* שדה: תוכן: כותרת */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_course_target_id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: תוכן: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_course_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'admin/arava-reports/course/%/emails';
  $handler->display->display_options['menu']['title'] = 'Reports - Accommodation';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['courses_reports'] = array(
    t('Master'),
    t('נרשמים ללינה'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('משתמש'),
    t('סוג לינה'),
    t('שם'),
    t('שם מלא'),
    t('טלפון'),
    t('Course'),
    t('נרשמים לקורס:'),
    t('my_courses'),
    t('field_course'),
    t('כותרת'),
    t('אימייל'),
    t('מחיקה מהקורס'),
    t('הכל'),
    t('[field_user_name] <[mail]>;'),
  );
  $export['courses_reports'] = $view;

  $view = new view();
  $view->name = 'invited_guests';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Invited Guests';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Invited Guests';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    13 => '13',
    4 => '4',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* שדה: תוכן: Extra Guests Num. */
  $handler->display->display_options['fields']['field_extra_guests_num']['id'] = 'field_extra_guests_num';
  $handler->display->display_options['fields']['field_extra_guests_num']['table'] = 'field_data_field_extra_guests_num';
  $handler->display->display_options['fields']['field_extra_guests_num']['field'] = 'field_extra_guests_num';
  $handler->display->display_options['fields']['field_extra_guests_num']['label'] = 'Guests Num.';
  $handler->display->display_options['fields']['field_extra_guests_num']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: משתמש: שם מלא (field_user_name) */
  $handler->display->display_options['sorts']['field_user_name_value']['id'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['sorts']['field_user_name_value']['field'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['relationship'] = 'field_user_target_id';
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'invited-guests';
  $translatables['invited_guests'] = array(
    t('Master'),
    t('Invited Guests'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('משתמש entity referenced from field_user'),
    t('שם מלא'),
    t('כתובת דוא"ל'),
    t('טלפון'),
    t('Guests Num.'),
    t('סמסטר'),
    t('Page'),
  );
  $export['invited_guests'] = $view;

  $view = new view();
  $view->name = 'invited_guests2';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Invited Guests2';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Invited Guests2';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« לעמוד הראשון';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ לעמוד הקודם';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'לעמוד הבא ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'לעמוד האחרון »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['relationship'] = 'uid';
  /* שדה: משתמש: שם */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* שדה: תוכן: Extra Guests Num. */
  $handler->display->display_options['fields']['field_extra_guests_num']['id'] = 'field_extra_guests_num';
  $handler->display->display_options['fields']['field_extra_guests_num']['table'] = 'field_data_field_extra_guests_num';
  $handler->display->display_options['fields']['field_extra_guests_num']['field'] = 'field_extra_guests_num';
  $handler->display->display_options['fields']['field_extra_guests_num']['relationship'] = 'field_semester_target_id';
  $handler->display->display_options['fields']['field_extra_guests_num']['label'] = 'Guests Num.';
  $handler->display->display_options['fields']['field_extra_guests_num']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: משתמש: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: משתמש: פעיל */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'invited-guests2';
  $translatables['invited_guests2'] = array(
    t('Master'),
    t('Invited Guests2'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« לעמוד הראשון'),
    t('‹ לעמוד הקודם'),
    t('לעמוד הבא ›'),
    t('לעמוד האחרון »'),
    t('תוכן entity referenced from field_semester'),
    t('Guests Num.'),
    t('Page'),
  );
  $export['invited_guests2'] = $view;

  $view = new view();
  $view->name = 'presence_reports';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Presence Reports';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'נוכחים ביום:';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view arava administration reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* כותרת: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<h1><?php
print t(arg(3));
?></h1>
<?php
print view_get_link_to_send_emails($view);
?>';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['label'] = 'משתמש';
  $handler->display->display_options['relationships']['field_user_target_id']['required'] = TRUE;
  /* שדה: תוכן: My Accomodation */
  $handler->display->display_options['fields']['field_my_accomodation']['id'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['field'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['label'] = 'סוג לינה';
  $handler->display->display_options['fields']['field_my_accomodation']['settings'] = array(
    'link' => 0,
  );
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = 'שם';
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name_1']['id'] = 'field_user_name_1';
  $handler->display->display_options['fields']['field_user_name_1']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name_1']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name_1']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* Contextual filter: תוכן: ימי נוכחות (field_days_present) */
  $handler->display->display_options['arguments']['field_days_present_value']['id'] = 'field_days_present_value';
  $handler->display->display_options['arguments']['field_days_present_value']['table'] = 'field_data_field_days_present';
  $handler->display->display_options['arguments']['field_days_present_value']['field'] = 'field_days_present_value';
  $handler->display->display_options['arguments']['field_days_present_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_days_present_value']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['field_days_present_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_days_present_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_days_present_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_days_present_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_days_present_value']['limit'] = '0';
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );

  /* Display: Presence */
  $handler = $view->new_display('page', 'Presence', 'page');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = 'שם';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['mail']['label'] = 'אימייל';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: משתמש: שם מלא (field_user_name) */
  $handler->display->display_options['sorts']['field_user_name_value']['id'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['sorts']['field_user_name_value']['field'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['path'] = 'admin/arava-reports/presence/%/list';
  $handler->display->display_options['menu']['title'] = 'Reports - Accommodation';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['presence_reports'] = array(
    t('Master'),
    t('נוכחים ביום:'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('משתמש'),
    t('סוג לינה'),
    t('שם'),
    t('שם מלא'),
    t('טלפון'),
    t('הכל'),
    t('סמסטר'),
    t('Presence'),
    t('אימייל'),
  );
  $export['presence_reports'] = $view;

  $view = new view();
  $view->name = 'reports';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Accommodation Reports';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'נרשמים ללינה מסוג:';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view arava administration reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* כותרת: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<h1><?php
print $results[0]->field_field_my_accomodation[0][\'rendered\'][\'#markup\'];
?></h1>
<?php
print view_get_link_to_send_emails($view);
?>';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['label'] = 'משתמש';
  $handler->display->display_options['relationships']['field_user_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_my_accomodation_target_id']['id'] = 'field_my_accomodation_target_id';
  $handler->display->display_options['relationships']['field_my_accomodation_target_id']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['relationships']['field_my_accomodation_target_id']['field'] = 'field_my_accomodation_target_id';
  $handler->display->display_options['relationships']['field_my_accomodation_target_id']['label'] = 'accommodation';
  $handler->display->display_options['relationships']['field_my_accomodation_target_id']['required'] = TRUE;
  /* שדה: תוכן: My Accomodation */
  $handler->display->display_options['fields']['field_my_accomodation']['id'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['field'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['label'] = 'סוג לינה';
  $handler->display->display_options['fields']['field_my_accomodation']['settings'] = array(
    'link' => 0,
  );
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = 'שם';
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name_1']['id'] = 'field_user_name_1';
  $handler->display->display_options['fields']['field_user_name_1']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name_1']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name_1']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* Contextual filter: תוכן: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_my_accomodation_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: תוכן: Semester (field_semester) */
  $handler->display->display_options['arguments']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['arguments']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['arguments']['field_semester_target_id']['field'] = 'field_semester_target_id';
  $handler->display->display_options['arguments']['field_semester_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_semester_target_id']['exception']['title'] = 'הכל';
  $handler->display->display_options['arguments']['field_semester_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_semester_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_semester_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_semester_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );

  /* Display: Accommodation */
  $handler = $view->new_display('page', 'Accommodation', 'page');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* שדה: תוכן: My Accomodation */
  $handler->display->display_options['fields']['field_my_accomodation']['id'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['field'] = 'field_my_accomodation';
  $handler->display->display_options['fields']['field_my_accomodation']['label'] = 'סוג לינה';
  $handler->display->display_options['fields']['field_my_accomodation']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_my_accomodation']['settings'] = array(
    'link' => 0,
  );
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['field_user_name']['label'] = 'שם';
  /* שדה: תוכן: Roommates */
  $handler->display->display_options['fields']['field_roommates']['id'] = 'field_roommates';
  $handler->display->display_options['fields']['field_roommates']['table'] = 'field_data_field_roommates';
  $handler->display->display_options['fields']['field_roommates']['field'] = 'field_roommates';
  $handler->display->display_options['fields']['field_roommates']['label'] = 'שותפים רצויים';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  $handler->display->display_options['fields']['mail']['label'] = 'אימייל';
  /* שדה: תוכן: ימי נוכחות */
  $handler->display->display_options['fields']['field_days_present']['id'] = 'field_days_present';
  $handler->display->display_options['fields']['field_days_present']['table'] = 'field_data_field_days_present';
  $handler->display->display_options['fields']['field_days_present']['field'] = 'field_days_present';
  $handler->display->display_options['fields']['field_days_present']['label'] = 'נמצא בימים';
  $handler->display->display_options['fields']['field_days_present']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: תוכן: My Accomodation (field_my_accomodation) */
  $handler->display->display_options['sorts']['field_my_accomodation_target_id']['id'] = 'field_my_accomodation_target_id';
  $handler->display->display_options['sorts']['field_my_accomodation_target_id']['table'] = 'field_data_field_my_accomodation';
  $handler->display->display_options['sorts']['field_my_accomodation_target_id']['field'] = 'field_my_accomodation_target_id';
  $handler->display->display_options['sorts']['field_my_accomodation_target_id']['expose']['label'] = 'סוג לינה';
  $handler->display->display_options['path'] = 'admin/arava-reports/accommodation/%/%/list';
  $handler->display->display_options['menu']['title'] = 'Reports - Accommodation';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['reports'] = array(
    t('Master'),
    t('נרשמים ללינה מסוג:'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('משתמש'),
    t('accommodation'),
    t('סוג לינה'),
    t('שם'),
    t('שם מלא'),
    t('טלפון'),
    t('הכל'),
    t('Accommodation'),
    t('שותפים רצויים'),
    t('אימייל'),
    t('נמצא בימים'),
  );
  $export['reports'] = $view;

  $view = new view();
  $view->name = 'semester_users';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Semester users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Semester users';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    6 => '6',
    4 => '4',
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1000';
  $handler->display->display_options['style_plugin'] = 'table';
  /* כותרת: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php
print view_get_link_to_send_emails($view);
?>
';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_user_target_id']['id'] = 'field_user_target_id';
  $handler->display->display_options['relationships']['field_user_target_id']['table'] = 'field_data_field_user';
  $handler->display->display_options['relationships']['field_user_target_id']['field'] = 'field_user_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_semester_target_id']['id'] = 'field_semester_target_id';
  $handler->display->display_options['relationships']['field_semester_target_id']['table'] = 'field_data_field_semester';
  $handler->display->display_options['relationships']['field_semester_target_id']['field'] = 'field_semester_target_id';
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_user_target_id';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['relationship'] = 'field_user_target_id';
  /* שדה: תוכן: ימי נוכחות */
  $handler->display->display_options['fields']['field_days_present']['id'] = 'field_days_present';
  $handler->display->display_options['fields']['field_days_present']['table'] = 'field_data_field_days_present';
  $handler->display->display_options['fields']['field_days_present']['field'] = 'field_days_present';
  $handler->display->display_options['fields']['field_days_present']['delta_offset'] = '0';
  /* שדה: משתמש: כתובת מגורים */
  $handler->display->display_options['fields']['field_user_address']['id'] = 'field_user_address';
  $handler->display->display_options['fields']['field_user_address']['table'] = 'field_data_field_user_address';
  $handler->display->display_options['fields']['field_user_address']['field'] = 'field_user_address';
  $handler->display->display_options['fields']['field_user_address']['relationship'] = 'field_user_target_id';
  /* שדה: תוכן: שעת הגעה */
  $handler->display->display_options['fields']['field_arrival_time']['id'] = 'field_arrival_time';
  $handler->display->display_options['fields']['field_arrival_time']['table'] = 'field_data_field_arrival_time';
  $handler->display->display_options['fields']['field_arrival_time']['field'] = 'field_arrival_time';
  $handler->display->display_options['fields']['field_arrival_time']['settings'] = array(
    'display_format' => array(
      'hour' => 'H',
      'minute' => 'i',
      'separator' => ':',
      'period' => 'none',
      'period_separator' => '',
    ),
  );
  /* שדה: תוכן: שעת עזיבה */
  $handler->display->display_options['fields']['field_departure_time']['id'] = 'field_departure_time';
  $handler->display->display_options['fields']['field_departure_time']['table'] = 'field_data_field_departure_time';
  $handler->display->display_options['fields']['field_departure_time']['field'] = 'field_departure_time';
  $handler->display->display_options['fields']['field_departure_time']['settings'] = array(
    'display_format' => array(
      'hour' => 'H',
      'minute' => 'i',
      'separator' => ':',
      'period' => 'none',
      'period_separator' => '',
    ),
  );
  /* Sort criterion: משתמש: שם מלא (field_user_name) */
  $handler->display->display_options['sorts']['field_user_name_value']['id'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['sorts']['field_user_name_value']['field'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['relationship'] = 'field_user_target_id';
  /* Filter criterion: תוכן: סוג */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'my_semester' => 'my_semester',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/semester-users';
  $translatables['semester_users'] = array(
    t('Master'),
    t('Semester users'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('משתמש entity referenced from field_user'),
    t('תוכן entity referenced from field_semester'),
    t('שם מלא'),
    t('כתובת דוא"ל'),
    t('טלפון'),
    t('ימי נוכחות'),
    t('כתובת מגורים'),
    t('שעת הגעה'),
    t('שעת עזיבה'),
    t('סמסטר'),
    t('Page'),
  );
  $export['semester_users'] = $view;

  $view = new view();
  $view->name = 'user_dining_needs';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'User Dining Needs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'User Dining Needs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    13 => '13',
    6 => '6',
    4 => '4',
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'איתחול';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_dairy' => 'field_dairy',
    'mail' => 'mail',
    'field_gluten' => 'field_gluten',
    'field_i_eat_dairy' => 'field_i_eat_dairy',
    'field_i_eat_eggs' => 'field_i_eat_eggs',
    'field_other_allergies' => 'field_other_allergies',
    'field_peanuts' => 'field_peanuts',
    'field_soy' => 'field_soy',
    'field_user_phone' => 'field_user_phone',
    'field_user_name' => 'field_user_name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_dairy' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gluten' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_i_eat_dairy' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_i_eat_eggs' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_other_allergies' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_peanuts' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_soy' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_user_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_user_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_user_node']['id'] = 'reverse_field_user_node';
  $handler->display->display_options['relationships']['reverse_field_user_node']['table'] = 'users';
  $handler->display->display_options['relationships']['reverse_field_user_node']['field'] = 'reverse_field_user_node';
  $handler->display->display_options['relationships']['reverse_field_user_node']['required'] = TRUE;
  /* שדה: משתמש: שם מלא */
  $handler->display->display_options['fields']['field_user_name']['id'] = 'field_user_name';
  $handler->display->display_options['fields']['field_user_name']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['fields']['field_user_name']['field'] = 'field_user_name';
  /* שדה: משתמש: כתובת דוא"ל */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  /* שדה: משתמש: טלפון */
  $handler->display->display_options['fields']['field_user_phone']['id'] = 'field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['table'] = 'field_data_field_user_phone';
  $handler->display->display_options['fields']['field_user_phone']['field'] = 'field_user_phone';
  /* שדה: משתמש: dairy allergy */
  $handler->display->display_options['fields']['field_dairy']['id'] = 'field_dairy';
  $handler->display->display_options['fields']['field_dairy']['table'] = 'field_data_field_dairy';
  $handler->display->display_options['fields']['field_dairy']['field'] = 'field_dairy';
  $handler->display->display_options['fields']['field_dairy']['type'] = 'list_key';
  /* שדה: משתמש: gluten allergy */
  $handler->display->display_options['fields']['field_gluten']['id'] = 'field_gluten';
  $handler->display->display_options['fields']['field_gluten']['table'] = 'field_data_field_gluten';
  $handler->display->display_options['fields']['field_gluten']['field'] = 'field_gluten';
  $handler->display->display_options['fields']['field_gluten']['type'] = 'list_key';
  /* שדה: משתמש: I eat dairy */
  $handler->display->display_options['fields']['field_i_eat_dairy']['id'] = 'field_i_eat_dairy';
  $handler->display->display_options['fields']['field_i_eat_dairy']['table'] = 'field_data_field_i_eat_dairy';
  $handler->display->display_options['fields']['field_i_eat_dairy']['field'] = 'field_i_eat_dairy';
  $handler->display->display_options['fields']['field_i_eat_dairy']['type'] = 'list_key';
  /* שדה: משתמש: I eat eggs */
  $handler->display->display_options['fields']['field_i_eat_eggs']['id'] = 'field_i_eat_eggs';
  $handler->display->display_options['fields']['field_i_eat_eggs']['table'] = 'field_data_field_i_eat_eggs';
  $handler->display->display_options['fields']['field_i_eat_eggs']['field'] = 'field_i_eat_eggs';
  $handler->display->display_options['fields']['field_i_eat_eggs']['type'] = 'list_key';
  /* שדה: משתמש: peanuts allergy */
  $handler->display->display_options['fields']['field_peanuts']['id'] = 'field_peanuts';
  $handler->display->display_options['fields']['field_peanuts']['table'] = 'field_data_field_peanuts';
  $handler->display->display_options['fields']['field_peanuts']['field'] = 'field_peanuts';
  $handler->display->display_options['fields']['field_peanuts']['type'] = 'list_key';
  /* שדה: משתמש: soy allergy */
  $handler->display->display_options['fields']['field_soy']['id'] = 'field_soy';
  $handler->display->display_options['fields']['field_soy']['table'] = 'field_data_field_soy';
  $handler->display->display_options['fields']['field_soy']['field'] = 'field_soy';
  $handler->display->display_options['fields']['field_soy']['type'] = 'list_key';
  /* שדה: משתמש: other allergies */
  $handler->display->display_options['fields']['field_other_allergies']['id'] = 'field_other_allergies';
  $handler->display->display_options['fields']['field_other_allergies']['table'] = 'field_data_field_other_allergies';
  $handler->display->display_options['fields']['field_other_allergies']['field'] = 'field_other_allergies';
  /* Sort criterion: משתמש: שם מלא (field_user_name) */
  $handler->display->display_options['sorts']['field_user_name_value']['id'] = 'field_user_name_value';
  $handler->display->display_options['sorts']['field_user_name_value']['table'] = 'field_data_field_user_name';
  $handler->display->display_options['sorts']['field_user_name_value']['field'] = 'field_user_name_value';
  /* Filter criterion: תוכן: registration complete (field_registration_complete) */
  $handler->display->display_options['filters']['field_registration_complete_value']['id'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['table'] = 'field_data_field_registration_complete';
  $handler->display->display_options['filters']['field_registration_complete_value']['field'] = 'field_registration_complete_value';
  $handler->display->display_options['filters']['field_registration_complete_value']['relationship'] = 'reverse_field_user_node';
  $handler->display->display_options['filters']['field_registration_complete_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: מותאם: סמסטר */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['relationship'] = 'reverse_field_user_node';
  $handler->display->display_options['filters']['semester']['value'] = array(
    'semester' => '2',
  );
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'סמסטר';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user-dining-needs';
  $translatables['user_dining_needs'] = array(
    t('Master'),
    t('User Dining Needs'),
    t('more'),
    t('Apply'),
    t('איתחול'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('תוכן referencing משתמש from field_user'),
    t('שם מלא'),
    t('כתובת דוא"ל'),
    t('טלפון'),
    t('dairy allergy'),
    t('gluten allergy'),
    t('I eat dairy'),
    t('I eat eggs'),
    t('peanuts allergy'),
    t('soy allergy'),
    t('other allergies'),
    t('סמסטר'),
    t('Page'),
  );
  $export['user_dining_needs'] = $view;

  return $export;
}
