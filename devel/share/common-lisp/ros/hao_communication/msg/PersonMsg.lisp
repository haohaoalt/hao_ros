; Auto-generated. Do not edit!


(cl:in-package hao_communication-msg)


;//! \htmlinclude PersonMsg.msg.html

(cl:defclass <PersonMsg> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (age
    :reader age
    :initarg :age
    :type cl:fixnum
    :initform 0)
   (sex
    :reader sex
    :initarg :sex
    :type cl:fixnum
    :initform 0))
)

(cl:defclass PersonMsg (<PersonMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PersonMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PersonMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hao_communication-msg:<PersonMsg> is deprecated: use hao_communication-msg:PersonMsg instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <PersonMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hao_communication-msg:name-val is deprecated.  Use hao_communication-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'age-val :lambda-list '(m))
(cl:defmethod age-val ((m <PersonMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hao_communication-msg:age-val is deprecated.  Use hao_communication-msg:age instead.")
  (age m))

(cl:ensure-generic-function 'sex-val :lambda-list '(m))
(cl:defmethod sex-val ((m <PersonMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hao_communication-msg:sex-val is deprecated.  Use hao_communication-msg:sex instead.")
  (sex m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<PersonMsg>)))
    "Constants for message type '<PersonMsg>"
  '((:UNKNOWN . 0)
    (:MALE . 1)
    (:FEMALE . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'PersonMsg)))
    "Constants for message type 'PersonMsg"
  '((:UNKNOWN . 0)
    (:MALE . 1)
    (:FEMALE . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PersonMsg>) ostream)
  "Serializes a message object of type '<PersonMsg>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'age)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sex)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PersonMsg>) istream)
  "Deserializes a message object of type '<PersonMsg>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'age)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sex)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PersonMsg>)))
  "Returns string type for a message object of type '<PersonMsg>"
  "hao_communication/PersonMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PersonMsg)))
  "Returns string type for a message object of type 'PersonMsg"
  "hao_communication/PersonMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PersonMsg>)))
  "Returns md5sum for a message object of type '<PersonMsg>"
  "b3f7ec37d11629ec3010e27635cf22a9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PersonMsg)))
  "Returns md5sum for a message object of type 'PersonMsg"
  "b3f7ec37d11629ec3010e27635cf22a9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PersonMsg>)))
  "Returns full string definition for message of type '<PersonMsg>"
  (cl:format cl:nil "string name~%uint8  age~%uint8  sex~%~%uint8 unknown = 0~%uint8 male    = 1~%uint8 female  = 2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PersonMsg)))
  "Returns full string definition for message of type 'PersonMsg"
  (cl:format cl:nil "string name~%uint8  age~%uint8  sex~%~%uint8 unknown = 0~%uint8 male    = 1~%uint8 female  = 2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PersonMsg>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PersonMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'PersonMsg
    (cl:cons ':name (name msg))
    (cl:cons ':age (age msg))
    (cl:cons ':sex (sex msg))
))
