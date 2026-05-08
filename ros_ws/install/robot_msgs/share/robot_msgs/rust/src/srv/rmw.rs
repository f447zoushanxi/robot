#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__DetectObject_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__srv__DetectObject_Request__init(msg: *mut DetectObject_Request) -> bool;
    fn robot_msgs__srv__DetectObject_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DetectObject_Request>, size: usize) -> bool;
    fn robot_msgs__srv__DetectObject_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DetectObject_Request>);
    fn robot_msgs__srv__DetectObject_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DetectObject_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<DetectObject_Request>) -> bool;
}

// Corresponds to robot_msgs__srv__DetectObject_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectObject_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub object_name: rosidl_runtime_rs::String,

    /// 服务调用超时（秒）
    pub timeout_sec: f32,

}



impl Default for DetectObject_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__srv__DetectObject_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__srv__DetectObject_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DetectObject_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__DetectObject_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__DetectObject_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__DetectObject_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DetectObject_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DetectObject_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/srv/DetectObject_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__DetectObject_Request() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__DetectObject_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__srv__DetectObject_Response__init(msg: *mut DetectObject_Response) -> bool;
    fn robot_msgs__srv__DetectObject_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DetectObject_Response>, size: usize) -> bool;
    fn robot_msgs__srv__DetectObject_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DetectObject_Response>);
    fn robot_msgs__srv__DetectObject_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DetectObject_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<DetectObject_Response>) -> bool;
}

// Corresponds to robot_msgs__srv__DetectObject_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectObject_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub found: bool,

    /// 目标在 base_link 坐标系下的 3D 位置
    pub position: geometry_msgs::msg::rmw::Point,

    /// 检测置信度 [0,1]
    pub confidence: f32,

    /// 输出坐标系名称
    pub frame_id: rosidl_runtime_rs::String,

    /// 额外调试信息
    pub message: rosidl_runtime_rs::String,

}



impl Default for DetectObject_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__srv__DetectObject_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__srv__DetectObject_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DetectObject_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__DetectObject_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__DetectObject_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__DetectObject_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DetectObject_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DetectObject_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/srv/DetectObject_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__DetectObject_Response() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__FindPerson_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__srv__FindPerson_Request__init(msg: *mut FindPerson_Request) -> bool;
    fn robot_msgs__srv__FindPerson_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<FindPerson_Request>, size: usize) -> bool;
    fn robot_msgs__srv__FindPerson_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<FindPerson_Request>);
    fn robot_msgs__srv__FindPerson_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<FindPerson_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<FindPerson_Request>) -> bool;
}

// Corresponds to robot_msgs__srv__FindPerson_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FindPerson_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub hint_name: rosidl_runtime_rs::String,

    /// 服务调用超时（秒）
    pub timeout_sec: f32,

}



impl Default for FindPerson_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__srv__FindPerson_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__srv__FindPerson_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for FindPerson_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__FindPerson_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__FindPerson_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__FindPerson_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for FindPerson_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for FindPerson_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/srv/FindPerson_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__FindPerson_Request() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__FindPerson_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__srv__FindPerson_Response__init(msg: *mut FindPerson_Response) -> bool;
    fn robot_msgs__srv__FindPerson_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<FindPerson_Response>, size: usize) -> bool;
    fn robot_msgs__srv__FindPerson_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<FindPerson_Response>);
    fn robot_msgs__srv__FindPerson_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<FindPerson_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<FindPerson_Response>) -> bool;
}

// Corresponds to robot_msgs__srv__FindPerson_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FindPerson_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub found: bool,

    /// 人员中心在 base_link 坐标系下的位置
    pub position: geometry_msgs::msg::rmw::Point,

    /// 置信度 [0,1]
    pub confidence: f32,

    /// 身份识别结果：owner/guest/unknown
    pub identity: rosidl_runtime_rs::String,

    /// 额外调试信息
    pub message: rosidl_runtime_rs::String,

}



impl Default for FindPerson_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__srv__FindPerson_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__srv__FindPerson_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for FindPerson_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__FindPerson_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__FindPerson_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__FindPerson_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for FindPerson_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for FindPerson_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/srv/FindPerson_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__FindPerson_Response() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__EnrollOwner_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__srv__EnrollOwner_Request__init(msg: *mut EnrollOwner_Request) -> bool;
    fn robot_msgs__srv__EnrollOwner_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EnrollOwner_Request>, size: usize) -> bool;
    fn robot_msgs__srv__EnrollOwner_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EnrollOwner_Request>);
    fn robot_msgs__srv__EnrollOwner_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EnrollOwner_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<EnrollOwner_Request>) -> bool;
}

// Corresponds to robot_msgs__srv__EnrollOwner_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EnrollOwner_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub require_physical_confirm: bool,

    /// 物理确认窗口时长（秒）
    pub window_sec: f32,

}



impl Default for EnrollOwner_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__srv__EnrollOwner_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__srv__EnrollOwner_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EnrollOwner_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__EnrollOwner_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__EnrollOwner_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__EnrollOwner_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EnrollOwner_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EnrollOwner_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/srv/EnrollOwner_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__EnrollOwner_Request() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__EnrollOwner_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__srv__EnrollOwner_Response__init(msg: *mut EnrollOwner_Response) -> bool;
    fn robot_msgs__srv__EnrollOwner_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EnrollOwner_Response>, size: usize) -> bool;
    fn robot_msgs__srv__EnrollOwner_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EnrollOwner_Response>);
    fn robot_msgs__srv__EnrollOwner_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EnrollOwner_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<EnrollOwner_Response>) -> bool;
}

// Corresponds to robot_msgs__srv__EnrollOwner_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EnrollOwner_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,

    /// owner id（成功时返回）
    pub owner_id: rosidl_runtime_rs::String,

    /// 结果说明
    pub message: rosidl_runtime_rs::String,

}



impl Default for EnrollOwner_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__srv__EnrollOwner_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__srv__EnrollOwner_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EnrollOwner_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__EnrollOwner_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__EnrollOwner_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__srv__EnrollOwner_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EnrollOwner_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EnrollOwner_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/srv/EnrollOwner_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__srv__EnrollOwner_Response() }
  }
}






#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__srv__DetectObject() -> *const std::ffi::c_void;
}

// Corresponds to robot_msgs__srv__DetectObject
#[allow(missing_docs, non_camel_case_types)]
pub struct DetectObject;

impl rosidl_runtime_rs::Service for DetectObject {
    type Request = DetectObject_Request;
    type Response = DetectObject_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__srv__DetectObject() }
    }
}




#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__srv__FindPerson() -> *const std::ffi::c_void;
}

// Corresponds to robot_msgs__srv__FindPerson
#[allow(missing_docs, non_camel_case_types)]
pub struct FindPerson;

impl rosidl_runtime_rs::Service for FindPerson {
    type Request = FindPerson_Request;
    type Response = FindPerson_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__srv__FindPerson() }
    }
}




#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__srv__EnrollOwner() -> *const std::ffi::c_void;
}

// Corresponds to robot_msgs__srv__EnrollOwner
#[allow(missing_docs, non_camel_case_types)]
pub struct EnrollOwner;

impl rosidl_runtime_rs::Service for EnrollOwner {
    type Request = EnrollOwner_Request;
    type Response = EnrollOwner_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__srv__EnrollOwner() }
    }
}


