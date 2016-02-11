// Auto-generated. Do not edit!

// (in-package driver_node.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class driver_setting {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.period = null;
      this.duty = null;
      this.wheel = null;
    }
    else {
      if (initObj.hasOwnProperty('period')) {
        this.period = initObj.period
      }
      else {
        this.period = 0;
      }
      if (initObj.hasOwnProperty('duty')) {
        this.duty = initObj.duty
      }
      else {
        this.duty = 0;
      }
      if (initObj.hasOwnProperty('wheel')) {
        this.wheel = initObj.wheel
      }
      else {
        this.wheel = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type driver_setting
    // Serialize message field [period]
    bufferOffset = _serializer.int32(obj.period, buffer, bufferOffset);
    // Serialize message field [duty]
    bufferOffset = _serializer.int8(obj.duty, buffer, bufferOffset);
    // Serialize message field [wheel]
    bufferOffset = _serializer.int8(obj.wheel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type driver_setting
    let len;
    let data = new driver_setting(null);
    // Deserialize message field [period]
    data.period = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [duty]
    data.duty = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [wheel]
    data.wheel = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'driver_node/driver_setting';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6697fb50f4e483911cb6c8595601db97';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 period
    int8 duty
    int8 wheel
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new driver_setting(null);
    if (msg.period !== undefined) {
      resolved.period = msg.period;
    }
    else {
      resolved.period = 0
    }

    if (msg.duty !== undefined) {
      resolved.duty = msg.duty;
    }
    else {
      resolved.duty = 0
    }

    if (msg.wheel !== undefined) {
      resolved.wheel = msg.wheel;
    }
    else {
      resolved.wheel = 0
    }

    return resolved;
    }
};

module.exports = driver_setting;
