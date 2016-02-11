; Auto-generated. Do not edit!


(cl:in-package driver_node-msg)


;//! \htmlinclude driver_setting.msg.html

(cl:defclass <driver_setting> (roslisp-msg-protocol:ros-message)
  ((period
    :reader period
    :initarg :period
    :type cl:integer
    :initform 0)
   (duty
    :reader duty
    :initarg :duty
    :type cl:fixnum
    :initform 0)
   (wheel
    :reader wheel
    :initarg :wheel
    :type cl:fixnum
    :initform 0))
)

(cl:defclass driver_setting (<driver_setting>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <driver_setting>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'driver_setting)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name driver_node-msg:<driver_setting> is deprecated: use driver_node-msg:driver_setting instead.")))

(cl:ensure-generic-function 'period-val :lambda-list '(m))
(cl:defmethod period-val ((m <driver_setting>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader driver_node-msg:period-val is deprecated.  Use driver_node-msg:period instead.")
  (period m))

(cl:ensure-generic-function 'duty-val :lambda-list '(m))
(cl:defmethod duty-val ((m <driver_setting>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader driver_node-msg:duty-val is deprecated.  Use driver_node-msg:duty instead.")
  (duty m))

(cl:ensure-generic-function 'wheel-val :lambda-list '(m))
(cl:defmethod wheel-val ((m <driver_setting>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader driver_node-msg:wheel-val is deprecated.  Use driver_node-msg:wheel instead.")
  (wheel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <driver_setting>) ostream)
  "Serializes a message object of type '<driver_setting>"
  (cl:let* ((signed (cl:slot-value msg 'period)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'duty)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'wheel)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <driver_setting>) istream)
  "Deserializes a message object of type '<driver_setting>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'period) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'duty) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'wheel) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<driver_setting>)))
  "Returns string type for a message object of type '<driver_setting>"
  "driver_node/driver_setting")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'driver_setting)))
  "Returns string type for a message object of type 'driver_setting"
  "driver_node/driver_setting")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<driver_setting>)))
  "Returns md5sum for a message object of type '<driver_setting>"
  "6697fb50f4e483911cb6c8595601db97")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'driver_setting)))
  "Returns md5sum for a message object of type 'driver_setting"
  "6697fb50f4e483911cb6c8595601db97")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<driver_setting>)))
  "Returns full string definition for message of type '<driver_setting>"
  (cl:format cl:nil "int32 period~%int8 duty~%int8 wheel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'driver_setting)))
  "Returns full string definition for message of type 'driver_setting"
  (cl:format cl:nil "int32 period~%int8 duty~%int8 wheel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <driver_setting>))
  (cl:+ 0
     4
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <driver_setting>))
  "Converts a ROS message object to a list"
  (cl:list 'driver_setting
    (cl:cons ':period (period msg))
    (cl:cons ':duty (duty msg))
    (cl:cons ':wheel (wheel msg))
))
