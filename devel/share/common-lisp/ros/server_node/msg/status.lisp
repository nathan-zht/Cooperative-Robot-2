; Auto-generated. Do not edit!


(cl:in-package server_node-msg)


;//! \htmlinclude status.msg.html

(cl:defclass <status> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:fixnum
    :initform 0)
   (x_pos
    :reader x_pos
    :initarg :x_pos
    :type cl:fixnum
    :initform 0)
   (y_pos
    :reader y_pos
    :initarg :y_pos
    :type cl:fixnum
    :initform 0))
)

(cl:defclass status (<status>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <status>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'status)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name server_node-msg:<status> is deprecated: use server_node-msg:status instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_node-msg:state-val is deprecated.  Use server_node-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'x_pos-val :lambda-list '(m))
(cl:defmethod x_pos-val ((m <status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_node-msg:x_pos-val is deprecated.  Use server_node-msg:x_pos instead.")
  (x_pos m))

(cl:ensure-generic-function 'y_pos-val :lambda-list '(m))
(cl:defmethod y_pos-val ((m <status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_node-msg:y_pos-val is deprecated.  Use server_node-msg:y_pos instead.")
  (y_pos m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <status>) ostream)
  "Serializes a message object of type '<status>"
  (cl:let* ((signed (cl:slot-value msg 'state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'x_pos)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y_pos)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <status>) istream)
  "Deserializes a message object of type '<status>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x_pos) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y_pos) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<status>)))
  "Returns string type for a message object of type '<status>"
  "server_node/status")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'status)))
  "Returns string type for a message object of type 'status"
  "server_node/status")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<status>)))
  "Returns md5sum for a message object of type '<status>"
  "6948d60b7d118ce47f95eddc739da798")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'status)))
  "Returns md5sum for a message object of type 'status"
  "6948d60b7d118ce47f95eddc739da798")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<status>)))
  "Returns full string definition for message of type '<status>"
  (cl:format cl:nil "int8 state~%int8 x_pos~%int8 y_pos~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'status)))
  "Returns full string definition for message of type 'status"
  (cl:format cl:nil "int8 state~%int8 x_pos~%int8 y_pos~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <status>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <status>))
  "Converts a ROS message object to a list"
  (cl:list 'status
    (cl:cons ':state (state msg))
    (cl:cons ':x_pos (x_pos msg))
    (cl:cons ':y_pos (y_pos msg))
))
