// Auto-generated. Do not edit!

// (in-package encoder_node.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class encoder_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ticks = null;
      this.direction = null;
    }
    else {
      if (initObj.hasOwnProperty('ticks')) {
        this.ticks = initObj.ticks
      }
      else {
        this.ticks = 0;
      }
      if (initObj.hasOwnProperty('direction')) {
        this.direction = initObj.direction
      }
      else {
        this.direction = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type encoder_msg
    // Serialize message field [ticks]
    bufferOffset = _serializer.int32(obj.ticks, buffer, bufferOffset);
    // Serialize message field [direction]
    bufferOffset = _serializer.int8(obj.direction, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type encoder_msg
    let len;
    let data = new encoder_msg(null);
    // Deserialize message field [ticks]
    data.ticks = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [direction]
    data.direction = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'encoder_node/encoder_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4e36c3dcce149655ed1ec27c09a76291';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 ticks
    int8  direction
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new encoder_msg(null);
    if (msg.ticks !== undefined) {
      resolved.ticks = msg.ticks;
    }
    else {
      resolved.ticks = 0
    }

    if (msg.direction !== undefined) {
      resolved.direction = msg.direction;
    }
    else {
      resolved.direction = 0
    }

    return resolved;
    }
};

module.exports = encoder_msg;
