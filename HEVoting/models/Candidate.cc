/**
 *
 *  Candidate.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Candidate.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::votingregister2;

const std::string Candidate::Cols::_poll = "poll";
const std::string Candidate::Cols::_name = "name";
const std::string Candidate::Cols::_ord = "ord";
const std::string Candidate::primaryKeyName = "";
const bool Candidate::hasPrimaryKey = false;
const std::string Candidate::tableName = "candidate";

const std::vector<typename Candidate::MetaData> Candidate::metaData_={
{"poll","int32_t","integer",4,0,0,1},
{"name","std::string","text",0,0,0,1},
{"ord","int32_t","integer",4,0,0,0}
};
const std::string &Candidate::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Candidate::Candidate(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["poll"].isNull())
        {
            poll_=std::make_shared<int32_t>(r["poll"].as<int32_t>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["ord"].isNull())
        {
            ord_=std::make_shared<int32_t>(r["ord"].as<int32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            poll_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            ord_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
    }

}

Candidate::Candidate(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            poll_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            name_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            ord_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
}

Candidate::Candidate(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("poll"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["poll"].isNull())
        {
            poll_=std::make_shared<int32_t>((int32_t)pJson["poll"].asInt64());
        }
    }
    if(pJson.isMember("name"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["name"].isNull())
        {
            name_=std::make_shared<std::string>(pJson["name"].asString());
        }
    }
    if(pJson.isMember("ord"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["ord"].isNull())
        {
            ord_=std::make_shared<int32_t>((int32_t)pJson["ord"].asInt64());
        }
    }
}

void Candidate::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            poll_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            name_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            ord_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
}

void Candidate::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("poll"))
    {
        dirtyFlag_[0] = true;
        if(!pJson["poll"].isNull())
        {
            poll_=std::make_shared<int32_t>((int32_t)pJson["poll"].asInt64());
        }
    }
    if(pJson.isMember("name"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["name"].isNull())
        {
            name_=std::make_shared<std::string>(pJson["name"].asString());
        }
    }
    if(pJson.isMember("ord"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["ord"].isNull())
        {
            ord_=std::make_shared<int32_t>((int32_t)pJson["ord"].asInt64());
        }
    }
}

const int32_t &Candidate::getValueOfPoll() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(poll_)
        return *poll_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Candidate::getPoll() const noexcept
{
    return poll_;
}
void Candidate::setPoll(const int32_t &pPoll) noexcept
{
    poll_ = std::make_shared<int32_t>(pPoll);
    dirtyFlag_[0] = true;
}

const std::string &Candidate::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Candidate::getName() const noexcept
{
    return name_;
}
void Candidate::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void Candidate::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const int32_t &Candidate::getValueOfOrd() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(ord_)
        return *ord_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Candidate::getOrd() const noexcept
{
    return ord_;
}
void Candidate::setOrd(const int32_t &pOrd) noexcept
{
    ord_ = std::make_shared<int32_t>(pOrd);
    dirtyFlag_[2] = true;
}
void Candidate::setOrdToNull() noexcept
{
    ord_.reset();
    dirtyFlag_[2] = true;
}

void Candidate::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Candidate::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "poll",
        "name",
        "ord"
    };
    return inCols;
}

void Candidate::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getPoll())
        {
            binder << getValueOfPoll();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getOrd())
        {
            binder << getValueOfOrd();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Candidate::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    return ret;
}

void Candidate::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getPoll())
        {
            binder << getValueOfPoll();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getOrd())
        {
            binder << getValueOfOrd();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Candidate::toJson() const
{
    Json::Value ret;
    if(getPoll())
    {
        ret["poll"]=getValueOfPoll();
    }
    else
    {
        ret["poll"]=Json::Value();
    }
    if(getName())
    {
        ret["name"]=getValueOfName();
    }
    else
    {
        ret["name"]=Json::Value();
    }
    if(getOrd())
    {
        ret["ord"]=getValueOfOrd();
    }
    else
    {
        ret["ord"]=Json::Value();
    }
    return ret;
}

Json::Value Candidate::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 3)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getPoll())
            {
                ret[pMasqueradingVector[0]]=getValueOfPoll();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getName())
            {
                ret[pMasqueradingVector[1]]=getValueOfName();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getOrd())
            {
                ret[pMasqueradingVector[2]]=getValueOfOrd();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getPoll())
    {
        ret["poll"]=getValueOfPoll();
    }
    else
    {
        ret["poll"]=Json::Value();
    }
    if(getName())
    {
        ret["name"]=getValueOfName();
    }
    else
    {
        ret["name"]=Json::Value();
    }
    if(getOrd())
    {
        ret["ord"]=getValueOfOrd();
    }
    else
    {
        ret["ord"]=Json::Value();
    }
    return ret;
}

bool Candidate::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("poll"))
    {
        if(!validJsonOfField(0, "poll", pJson["poll"], err, true))
            return false;
    }
    else
    {
        err="The poll column cannot be null";
        return false;
    }
    if(pJson.isMember("name"))
    {
        if(!validJsonOfField(1, "name", pJson["name"], err, true))
            return false;
    }
    else
    {
        err="The name column cannot be null";
        return false;
    }
    if(pJson.isMember("ord"))
    {
        if(!validJsonOfField(2, "ord", pJson["ord"], err, true))
            return false;
    }
    return true;
}
bool Candidate::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                   const std::vector<std::string> &pMasqueradingVector,
                                                   std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[0] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Candidate::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("poll"))
    {
        if(!validJsonOfField(0, "poll", pJson["poll"], err, false))
            return false;
    }
    if(pJson.isMember("name"))
    {
        if(!validJsonOfField(1, "name", pJson["name"], err, false))
            return false;
    }
    if(pJson.isMember("ord"))
    {
        if(!validJsonOfField(2, "ord", pJson["ord"], err, false))
            return false;
    }
    return true;
}
bool Candidate::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                 const std::vector<std::string> &pMasqueradingVector,
                                                 std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Candidate::validJsonOfField(size_t index,
                                 const std::string &fieldName,
                                 const Json::Value &pJson,
                                 std::string &err,
                                 bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
