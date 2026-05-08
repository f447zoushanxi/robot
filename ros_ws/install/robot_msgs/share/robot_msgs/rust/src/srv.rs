#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to robot_msgs__srv__DetectObject_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectObject_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub object_name: std::string::String,

    /// 服务调用超时（秒）
    pub timeout_sec: f32,

}



impl Default for DetectObject_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::DetectObject_Request::default())
  }
}

impl rosidl_runtime_rs::Message for DetectObject_Request {
  type RmwMsg = super::srv::rmw::DetectObject_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        object_name: msg.object_name.as_str().into(),
        timeout_sec: msg.timeout_sec,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        object_name: msg.object_name.as_str().into(),
      timeout_sec: msg.timeout_sec,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      object_name: msg.object_name.to_string(),
      timeout_sec: msg.timeout_sec,
    }
  }
}


// Corresponds to robot_msgs__srv__DetectObject_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectObject_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub found: bool,

    /// 目标在 base_link 坐标系下的 3D 位置
    pub position: geometry_msgs::msg::Point,

    /// 检测置信度 [0,1]
    pub confidence: f32,

    /// 输出坐标系名称
    pub frame_id: std::string::String,

    /// 额外调试信息
    pub message: std::string::String,

}



impl Default for DetectObject_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::DetectObject_Response::default())
  }
}

impl rosidl_runtime_rs::Message for DetectObject_Response {
  type RmwMsg = super::srv::rmw::DetectObject_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        found: msg.found,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.position)).into_owned(),
        confidence: msg.confidence,
        frame_id: msg.frame_id.as_str().into(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      found: msg.found,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.position)).into_owned(),
      confidence: msg.confidence,
        frame_id: msg.frame_id.as_str().into(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      found: msg.found,
      position: geometry_msgs::msg::Point::from_rmw_message(msg.position),
      confidence: msg.confidence,
      frame_id: msg.frame_id.to_string(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to robot_msgs__srv__FindPerson_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FindPerson_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub hint_name: std::string::String,

    /// 服务调用超时（秒）
    pub timeout_sec: f32,

}



impl Default for FindPerson_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::FindPerson_Request::default())
  }
}

impl rosidl_runtime_rs::Message for FindPerson_Request {
  type RmwMsg = super::srv::rmw::FindPerson_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        hint_name: msg.hint_name.as_str().into(),
        timeout_sec: msg.timeout_sec,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        hint_name: msg.hint_name.as_str().into(),
      timeout_sec: msg.timeout_sec,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      hint_name: msg.hint_name.to_string(),
      timeout_sec: msg.timeout_sec,
    }
  }
}


// Corresponds to robot_msgs__srv__FindPerson_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FindPerson_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub found: bool,

    /// 人员中心在 base_link 坐标系下的位置
    pub position: geometry_msgs::msg::Point,

    /// 置信度 [0,1]
    pub confidence: f32,

    /// 身份识别结果：owner/guest/unknown
    pub identity: std::string::String,

    /// 额外调试信息
    pub message: std::string::String,

}



impl Default for FindPerson_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::FindPerson_Response::default())
  }
}

impl rosidl_runtime_rs::Message for FindPerson_Response {
  type RmwMsg = super::srv::rmw::FindPerson_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        found: msg.found,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.position)).into_owned(),
        confidence: msg.confidence,
        identity: msg.identity.as_str().into(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      found: msg.found,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.position)).into_owned(),
      confidence: msg.confidence,
        identity: msg.identity.as_str().into(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      found: msg.found,
      position: geometry_msgs::msg::Point::from_rmw_message(msg.position),
      confidence: msg.confidence,
      identity: msg.identity.to_string(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to robot_msgs__srv__EnrollOwner_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::EnrollOwner_Request::default())
  }
}

impl rosidl_runtime_rs::Message for EnrollOwner_Request {
  type RmwMsg = super::srv::rmw::EnrollOwner_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        require_physical_confirm: msg.require_physical_confirm,
        window_sec: msg.window_sec,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      require_physical_confirm: msg.require_physical_confirm,
      window_sec: msg.window_sec,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      require_physical_confirm: msg.require_physical_confirm,
      window_sec: msg.window_sec,
    }
  }
}


// Corresponds to robot_msgs__srv__EnrollOwner_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EnrollOwner_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,

    /// owner id（成功时返回）
    pub owner_id: std::string::String,

    /// 结果说明
    pub message: std::string::String,

}



impl Default for EnrollOwner_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::EnrollOwner_Response::default())
  }
}

impl rosidl_runtime_rs::Message for EnrollOwner_Response {
  type RmwMsg = super::srv::rmw::EnrollOwner_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        owner_id: msg.owner_id.as_str().into(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        owner_id: msg.owner_id.as_str().into(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      owner_id: msg.owner_id.to_string(),
      message: msg.message.to_string(),
    }
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


