// Generated by gencpp from file server_node/status.msg
// DO NOT EDIT!


#ifndef SERVER_NODE_MESSAGE_STATUS_H
#define SERVER_NODE_MESSAGE_STATUS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace server_node
{
template <class ContainerAllocator>
struct status_
{
  typedef status_<ContainerAllocator> Type;

  status_()
    : state(0)
    , x_pos(0)
    , y_pos(0)  {
    }
  status_(const ContainerAllocator& _alloc)
    : state(0)
    , x_pos(0)
    , y_pos(0)  {
  (void)_alloc;
    }



   typedef int8_t _state_type;
  _state_type state;

   typedef int8_t _x_pos_type;
  _x_pos_type x_pos;

   typedef int8_t _y_pos_type;
  _y_pos_type y_pos;





  typedef boost::shared_ptr< ::server_node::status_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::server_node::status_<ContainerAllocator> const> ConstPtr;

}; // struct status_

typedef ::server_node::status_<std::allocator<void> > status;

typedef boost::shared_ptr< ::server_node::status > statusPtr;
typedef boost::shared_ptr< ::server_node::status const> statusConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::server_node::status_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::server_node::status_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace server_node

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'server_node': ['/home/xillinux/cobot/catkin_ws/src/server_node/msg'], 'std_msgs': ['/opt/ros/lunar/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::server_node::status_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::server_node::status_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::server_node::status_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::server_node::status_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::server_node::status_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::server_node::status_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::server_node::status_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6948d60b7d118ce47f95eddc739da798";
  }

  static const char* value(const ::server_node::status_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6948d60b7d118ce4ULL;
  static const uint64_t static_value2 = 0x7f95eddc739da798ULL;
};

template<class ContainerAllocator>
struct DataType< ::server_node::status_<ContainerAllocator> >
{
  static const char* value()
  {
    return "server_node/status";
  }

  static const char* value(const ::server_node::status_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::server_node::status_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 state\n\
int8 x_pos\n\
int8 y_pos\n\
";
  }

  static const char* value(const ::server_node::status_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::server_node::status_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.state);
      stream.next(m.x_pos);
      stream.next(m.y_pos);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct status_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::server_node::status_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::server_node::status_<ContainerAllocator>& v)
  {
    s << indent << "state: ";
    Printer<int8_t>::stream(s, indent + "  ", v.state);
    s << indent << "x_pos: ";
    Printer<int8_t>::stream(s, indent + "  ", v.x_pos);
    s << indent << "y_pos: ";
    Printer<int8_t>::stream(s, indent + "  ", v.y_pos);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SERVER_NODE_MESSAGE_STATUS_H
