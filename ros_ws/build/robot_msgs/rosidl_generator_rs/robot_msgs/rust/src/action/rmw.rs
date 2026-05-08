
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_Goal() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_Goal__init(msg: *mut PickBottle_Goal) -> bool;
    fn robot_msgs__action__PickBottle_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Goal>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Goal>);
    fn robot_msgs__action__PickBottle_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Goal>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub object_name: rosidl_runtime_rs::String,

}



impl Default for PickBottle_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_Goal__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_Goal() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_Result() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_Result__init(msg: *mut PickBottle_Result) -> bool;
    fn robot_msgs__action__PickBottle_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Result>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Result>);
    fn robot_msgs__action__PickBottle_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Result>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for PickBottle_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_Result__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_Result where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_Result() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_Feedback__init(msg: *mut PickBottle_Feedback) -> bool;
    fn robot_msgs__action__PickBottle_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Feedback>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Feedback>);
    fn robot_msgs__action__PickBottle_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_Feedback>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stage: rosidl_runtime_rs::String,

}



impl Default for PickBottle_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_Feedback__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_Feedback() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_FeedbackMessage__init(msg: *mut PickBottle_FeedbackMessage) -> bool;
    fn robot_msgs__action__PickBottle_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_FeedbackMessage>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_FeedbackMessage>);
    fn robot_msgs__action__PickBottle_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_FeedbackMessage>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::PickBottle_Feedback,

}



impl Default for PickBottle_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_FeedbackMessage() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_Goal() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_Goal__init(msg: *mut HandOver_Goal) -> bool;
    fn robot_msgs__action__HandOver_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_Goal>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_Goal>);
    fn robot_msgs__action__HandOver_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_Goal>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target_identity: rosidl_runtime_rs::String,

}



impl Default for HandOver_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_Goal__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_Goal() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_Result() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_Result__init(msg: *mut HandOver_Result) -> bool;
    fn robot_msgs__action__HandOver_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_Result>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_Result>);
    fn robot_msgs__action__HandOver_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_Result>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for HandOver_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_Result__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_Result where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_Result() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_Feedback__init(msg: *mut HandOver_Feedback) -> bool;
    fn robot_msgs__action__HandOver_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_Feedback>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_Feedback>);
    fn robot_msgs__action__HandOver_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_Feedback>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stage: rosidl_runtime_rs::String,

}



impl Default for HandOver_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_Feedback__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_Feedback() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_FeedbackMessage__init(msg: *mut HandOver_FeedbackMessage) -> bool;
    fn robot_msgs__action__HandOver_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_FeedbackMessage>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_FeedbackMessage>);
    fn robot_msgs__action__HandOver_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_FeedbackMessage>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::HandOver_Feedback,

}



impl Default for HandOver_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_FeedbackMessage() }
  }
}




#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_SendGoal_Request__init(msg: *mut PickBottle_SendGoal_Request) -> bool;
    fn robot_msgs__action__PickBottle_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Request>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Request>);
    fn robot_msgs__action__PickBottle_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Request>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::PickBottle_Goal,

}



impl Default for PickBottle_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_SendGoal_Request() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_SendGoal_Response__init(msg: *mut PickBottle_SendGoal_Response) -> bool;
    fn robot_msgs__action__PickBottle_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Response>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Response>);
    fn robot_msgs__action__PickBottle_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_SendGoal_Response>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for PickBottle_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_SendGoal_Response() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_GetResult_Request__init(msg: *mut PickBottle_GetResult_Request) -> bool;
    fn robot_msgs__action__PickBottle_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_GetResult_Request>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_GetResult_Request>);
    fn robot_msgs__action__PickBottle_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_GetResult_Request>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for PickBottle_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_GetResult_Request() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__PickBottle_GetResult_Response__init(msg: *mut PickBottle_GetResult_Response) -> bool;
    fn robot_msgs__action__PickBottle_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_GetResult_Response>, size: usize) -> bool;
    fn robot_msgs__action__PickBottle_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBottle_GetResult_Response>);
    fn robot_msgs__action__PickBottle_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBottle_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBottle_GetResult_Response>) -> bool;
}

// Corresponds to robot_msgs__action__PickBottle_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBottle_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::PickBottle_Result,

}



impl Default for PickBottle_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__PickBottle_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__PickBottle_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBottle_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__PickBottle_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBottle_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBottle_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/PickBottle_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__PickBottle_GetResult_Response() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_SendGoal_Request__init(msg: *mut HandOver_SendGoal_Request) -> bool;
    fn robot_msgs__action__HandOver_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_SendGoal_Request>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_SendGoal_Request>);
    fn robot_msgs__action__HandOver_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_SendGoal_Request>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::HandOver_Goal,

}



impl Default for HandOver_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_SendGoal_Request() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_SendGoal_Response__init(msg: *mut HandOver_SendGoal_Response) -> bool;
    fn robot_msgs__action__HandOver_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_SendGoal_Response>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_SendGoal_Response>);
    fn robot_msgs__action__HandOver_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_SendGoal_Response>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for HandOver_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_SendGoal_Response() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_GetResult_Request__init(msg: *mut HandOver_GetResult_Request) -> bool;
    fn robot_msgs__action__HandOver_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_GetResult_Request>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_GetResult_Request>);
    fn robot_msgs__action__HandOver_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_GetResult_Request>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for HandOver_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_GetResult_Request() }
  }
}


#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_msgs__rosidl_generator_c")]
extern "C" {
    fn robot_msgs__action__HandOver_GetResult_Response__init(msg: *mut HandOver_GetResult_Response) -> bool;
    fn robot_msgs__action__HandOver_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandOver_GetResult_Response>, size: usize) -> bool;
    fn robot_msgs__action__HandOver_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandOver_GetResult_Response>);
    fn robot_msgs__action__HandOver_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandOver_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<HandOver_GetResult_Response>) -> bool;
}

// Corresponds to robot_msgs__action__HandOver_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandOver_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::HandOver_Result,

}



impl Default for HandOver_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_msgs__action__HandOver_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_msgs__action__HandOver_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandOver_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_msgs__action__HandOver_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandOver_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandOver_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_msgs/action/HandOver_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_msgs__action__HandOver_GetResult_Response() }
  }
}






#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__PickBottle_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to robot_msgs__action__PickBottle_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct PickBottle_SendGoal;

impl rosidl_runtime_rs::Service for PickBottle_SendGoal {
    type Request = PickBottle_SendGoal_Request;
    type Response = PickBottle_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__PickBottle_SendGoal() }
    }
}




#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__PickBottle_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to robot_msgs__action__PickBottle_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct PickBottle_GetResult;

impl rosidl_runtime_rs::Service for PickBottle_GetResult {
    type Request = PickBottle_GetResult_Request;
    type Response = PickBottle_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__PickBottle_GetResult() }
    }
}




#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__HandOver_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to robot_msgs__action__HandOver_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct HandOver_SendGoal;

impl rosidl_runtime_rs::Service for HandOver_SendGoal {
    type Request = HandOver_SendGoal_Request;
    type Response = HandOver_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__HandOver_SendGoal() }
    }
}




#[link(name = "robot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__HandOver_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to robot_msgs__action__HandOver_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct HandOver_GetResult;

impl rosidl_runtime_rs::Service for HandOver_GetResult {
    type Request = HandOver_GetResult_Request;
    type Response = HandOver_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_msgs__action__HandOver_GetResult() }
    }
}


