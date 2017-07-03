// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef air_RpcLibCustomSerializers_hpp
#define air_RpcLibCustomSerializers_hpp

#include "common/Common.hpp"
#include "common/CommonStructs.hpp"
#include "controllers/DroneCommon.hpp"
#include "controllers/DroneControllerBase.hpp"
#include "safety/SafetyEval.hpp"
#include "rpc/msgpack.hpp"


namespace msr { namespace airlib_rpclib {

class RpcLibAdapators {
public:
    template<typename TSrc, typename TDest>
    static void to(const std::vector<TSrc>& s, std::vector<TDest>& d)
    {
        d.clear();
        for (size_t i = 0; i < s.size(); ++i)
            d.push_back(s.at(i).to());
    }

    template<typename TSrc, typename TDest>
    static void from(const std::vector<TSrc>& s, std::vector<TDest>& d)
    {
        d.clear();
        for (size_t i = 0; i < s.size(); ++i)
            d.push_back(TDest(s.at(i)));
    }

    struct YawMode {
        bool is_rate;
        float yaw_or_rate;
        MSGPACK_DEFINE_ARRAY(is_rate, yaw_or_rate);
    
        YawMode()
        {}

        YawMode(const msr::airlib::YawMode& s)
        {
            is_rate = s.is_rate;
            yaw_or_rate = s.yaw_or_rate;
        }
        msr::airlib::YawMode to() const
        {
            return msr::airlib::YawMode(is_rate, yaw_or_rate);
        }
    };

    struct Vector3r {
        msr::airlib::real_T x_ = 0, y_ = 0, z_ = 0;
        MSGPACK_DEFINE_ARRAY(x_, y_, z_);

        Vector3r()
        {}

        Vector3r(const msr::airlib::Vector3r& s)
        {
            x_ = s.x();
            y_ = s.y();
            z_ = s.z();
        }
        msr::airlib::Vector3r to() const
        {
            return msr::airlib::Vector3r(x_, y_, z_);
        }
    };

    struct CollisionInfo {
        bool has_collided = false;
        Vector3r normal;
        Vector3r impact_point;
        Vector3r position;
        msr::airlib::real_T penetration_depth = 0;
        msr::airlib::TTimePoint time_stamp = 0;

        MSGPACK_DEFINE_ARRAY(has_collided, penetration_depth, time_stamp, normal, impact_point, position);
        
        CollisionInfo()
        {}

        CollisionInfo(const msr::airlib::CollisionInfo& s)
        {
            has_collided = s.has_collided;
            penetration_depth = s.penetration_depth;
            time_stamp = s.time_stamp;
            normal = s.normal;
            impact_point = s.impact_point;
            position = s.position;
        }

        msr::airlib::CollisionInfo to() const
        {
            return msr::airlib::CollisionInfo(has_collided, normal.to(), impact_point.to(), position.to(),
                penetration_depth, time_stamp);
        }
    };

    struct Quaternionr {
        msr::airlib::real_T w_, x_, y_, z_;
        MSGPACK_DEFINE_ARRAY(w_, x_, y_, z_);

        Quaternionr()
        {}

        Quaternionr(const msr::airlib::Quaternionr& s)
        {
            w_ = s.w();
            x_ = s.x();
            y_ = s.y();
            z_ = s.z();
        }
        msr::airlib::Quaternionr to() const
        {
            return msr::airlib::Quaternionr(w_, x_, y_, z_);
        }
    };

    struct GeoPoint {
        double latitude = 0, longitude = 0;
        float altitude = 0;
        MSGPACK_DEFINE_ARRAY(latitude, longitude, altitude);

        GeoPoint()
        {}

        GeoPoint(const msr::airlib::GeoPoint& s)
        {
            latitude = s.latitude;
            longitude = s.longitude;
            altitude = s.altitude;
        }
        msr::airlib::GeoPoint to() const
        {
            return msr::airlib::GeoPoint(latitude, longitude, altitude);
        }
    };

    struct RCData {
        uint64_t timestamp = 0;
        float pitch = 0, roll = 0, throttle = 0, yaw = 0;
        unsigned int  switch1 = 0, switch2 = 0, switch3 = 0, switch4 = 0, 
            switch5 = 0, switch6 = 0, switch7 = 0, switch8 = 0;

        MSGPACK_DEFINE_ARRAY(timestamp, pitch, roll, throttle, yaw, switch1, switch2, switch3, switch4, switch5, switch6, switch7, switch8);

        RCData()
        {}

        RCData(const msr::airlib::RCData& s)
        {
            timestamp = s.timestamp;
            pitch = s.pitch;
            roll = s.roll;
            throttle = s.throttle;
            yaw = s.yaw;
            switch1 = s.switch1;
            switch2 = s.switch2;
            switch3 = s.switch3;
            switch4 = s.switch4;
            switch5 = s.switch5;
            switch6 = s.switch6;
            switch7 = s.switch7;
            switch8 = s.switch8;

        }
        msr::airlib::RCData to() const
        {
            msr::airlib::RCData d;
            d.timestamp = timestamp;
            d.pitch = pitch;
            d.roll = roll;
            d.throttle = throttle;
            d.yaw = yaw;
            d.switch1 = switch1;
            d.switch2 = switch2;
            d.switch3 = switch3;
            d.switch4 = switch4;
            d.switch5 = switch5;
            d.switch6 = switch6;
            d.switch7 = switch7;
            d.switch8 = switch8;
            
            return d;
        }
    };
};

}} //namespace

MSGPACK_ADD_ENUM(msr::airlib::DrivetrainType);
MSGPACK_ADD_ENUM(msr::airlib::SafetyEval::SafetyViolationType_);
MSGPACK_ADD_ENUM(msr::airlib::SafetyEval::ObsAvoidanceStrategy);
MSGPACK_ADD_ENUM(msr::airlib::VehicleCamera::ImageType);


#endif
