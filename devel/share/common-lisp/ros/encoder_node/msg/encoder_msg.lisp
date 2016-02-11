; Auto-generated. Do not edit!


(cl:in-package encoder_node-msg)


;//! \htmlinclude encoder_msg.msg.html

(cl:defclass <encoder_msg> (roslisp-msg-protocol:ros-message)
  ((ticks
    :reader ticks
    :initarg :ticks
    :type cl:integer
    :initform 0)
   (direction
    :reader direction
    :initarg :direction
    :type cl:fixnum
    :initform 0))
)

(cl:defclass encoder_msg (<encoder_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <encoder_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'encoder_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name encoder_node-msg:<encoder_msg> is deprecated: use encoder_node-msg:encoder_msg instead.")))

(cl:ensure-generic-function 'ticks-val :lambda-list '(m))
(cl:defmethod ticks-val ((m <encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader encoder_node-msg:ticks-val is deprecated.  Use encoder_node-msg:ticks instead.")
  (ticks m))

(cl:ensure-generic-function 'direction-val :lambda-list '(m))
(cl:defmethod direction-val ((m <encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader encoder_node-msg:direction-val is deprecated.  Use encoder_node-msg:direction instead.")
  (direction m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <encoder_msg>) ostream)
  "Serializes a message object of type '<encoder_msg>"
  (cl:let* ((signed (cl:slot-value msg 'ticks)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'direction)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <encoder_msg>) istream)
  "Deserializes a message object of type '<encoder_msg>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ticks) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'direction) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<encoder_msg>)))
  "Returns string type for a message object of type '<encoder_msg>"
  "encoder_node/encoder_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'encoder_msg)))
  "Returns string type for a message object of type 'encoder_msg"
  "encoder_node/encoder_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<encoder_msg>)))
  "Returns md5sum for a message object of type '<encoder_msg>"
  "4e36c3dcce149655ed1ec27c09a76291")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'encoder_msg)))
  "Returns md5sum for a message object of type 'encoder_msg"
  "4e36c3dcce149655ed1ec27c09a76291")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<encoder_msg>)))
  "Returns full string definition for message of type '<encoder_msg>"
  (cl:format cl:nil "int32 ticks~%int8  direction~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'encoder_msg)))
  "Returns full string definition for message of type 'encoder_msg"
  (cl:format cl:nil "int32 ticks~%int8  direction~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <encoder_msg>))
  (cl:+ 0
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <encoder_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'encoder_msg
    (cl:cons ':ticks (ticks msg))
    (cl:cons ':direction (direction msg))
))
