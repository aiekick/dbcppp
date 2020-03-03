
#include "Network.h"
#include "NetworkImpl.h"
#include "DBC_Grammar.h"

using namespace dbcppp;

std::unique_ptr<Network> Network::create(
	  std::string&& version
	, std::set<std::string>&& new_symbols
	, std::unique_ptr<BitTiming>&& bit_timing
	, std::map<std::string, std::unique_ptr<Node>>&& nodes
	, std::map<std::string, std::unique_ptr<ValueTable>>&& value_tables
	, std::unordered_map<uint64_t, std::unique_ptr<Message>>&& messages
	, std::map<std::string, std::unique_ptr<EnvironmentVariable>>&& environment_variables
	, std::map<std::string, std::unique_ptr<AttributeDefinition>>&& attribute_definitions
	, std::map<std::string, std::unique_ptr<Attribute>>&& attribute_defaults
	, std::map<std::string, std::unique_ptr<Attribute>>&& attribute_values
	, std::string&& comment)
{
	BitTimingImpl bt = std::move(static_cast<BitTimingImpl&>(*bit_timing));
	bit_timing.reset(nullptr);
	std::map<std::string, NodeImpl> ns;
	std::map<std::string, ValueTableImpl> vts;
	std::unordered_map<uint64_t, MessageImpl> ms;
	std::map<std::string, EnvironmentVariableImpl> evs;
	std::map<std::string, AttributeDefinitionImpl> ads;
	std::map<std::string, AttributeImpl> avds;
	std::map<std::string, AttributeImpl> avs;
	for (auto& n : nodes)
	{
		ns.insert(std::make_pair(n.first, std::move(static_cast<NodeImpl&>(*n.second))));
		n.second.reset(nullptr);
	}
	for (auto& vt : value_tables)
	{
		vts.insert(std::make_pair(vt.first, std::move(static_cast<ValueTableImpl&>(*vt.second))));
		vt.second.reset(nullptr);
	}
	for (auto& m : messages)
	{
		ms.insert(std::make_pair(m.first, std::move(static_cast<MessageImpl&>(*m.second))));
		m.second.reset(nullptr);
	}
	for (auto& ev : environment_variables)
	{
		evs.insert(std::make_pair(ev.first, std::move(static_cast<EnvironmentVariableImpl&>(*ev.second))));
		ev.second.reset(nullptr);
	}
	for (auto& ad : attribute_definitions)
	{
		ads.insert(std::make_pair(ad.first, std::move(static_cast<AttributeDefinitionImpl&>(*ad.second))));
		ad.second.reset(nullptr);
	}
	for (auto& ad : attribute_defaults)
	{
		avds.insert(std::make_pair(ad.first, std::move(static_cast<AttributeImpl&>(*ad.second))));
		ad.second.reset(nullptr);
	}
	for (auto& ad : attribute_values)
	{
		avs.insert(std::make_pair(ad.first, std::move(static_cast<AttributeImpl&>(*ad.second))));
		ad.second.reset(nullptr);
	}
	return std::make_unique<NetworkImpl>(
		  std::move(version)
		, std::move(new_symbols)
		, std::move(bt)
		, std::move(ns)
		, std::move(vts)
		, std::move(ms)
		, std::move(evs)
		, std::move(ads)
		, std::move(avds)
		, std::move(avs)
		, std::move(comment));
}

NetworkImpl::NetworkImpl(
	  std::string&& version
	, std::set<std::string>&& new_symbols
	, BitTimingImpl&& bit_timing
	, std::map<std::string, NodeImpl>&& nodes
	, std::map<std::string, ValueTableImpl>&& value_tables
	, std::unordered_map<uint64_t, MessageImpl>&& messages
	, std::map<std::string, EnvironmentVariableImpl>&& environment_variables
	, std::map<std::string, AttributeDefinitionImpl>&& attribute_definitions
	, std::map<std::string, AttributeImpl>&& attribute_defaults
	, std::map<std::string, AttributeImpl>&& attribute_values
	, std::string&& comment)

	: _version(std::move(version))
	, _new_symbols(std::move(new_symbols))
	, _bit_timing(std::move(bit_timing))
	, _nodes(std::move(nodes))
	, _value_tables(std::move(value_tables))
	, _messages(std::move(messages))
	, _environment_variables(std::move(environment_variables))
	, _attribute_definitions(std::move(attribute_definitions))
	, _attribute_defaults(std::move(attribute_defaults))
	, _attribute_values(std::move(attribute_values))
	, _comment(std::move(comment))
{}
const std::string& NetworkImpl::getVersion() const
{
	return _version;
}
bool NetworkImpl::hasNewSymbol(const std::string& name) const
{
	return std::find(_new_symbols.begin(), _new_symbols.end(), name) != _new_symbols.end();
}
std::vector<const std::string*> NetworkImpl::getNewSymbols() const
{
	std::vector<const std::string*> result;
	for (auto& ns : _new_symbols)
	{
		result.emplace_back(&ns);
	}
	return result;
}
const BitTiming& NetworkImpl::getBitTiming() const
{
	return _bit_timing;
}
const Node* NetworkImpl::getNodeByName(const std::string& name) const
{
	const Node* result = nullptr;
	auto iter = _nodes.find(name);
	if (iter != _nodes.end())
	{
		result = &iter->second;
	}
	return result;
}
std::vector<std::pair<std::string, const Node*>> NetworkImpl::getNodes() const
{
	std::vector<std::pair<std::string, const Node*>> result;
	for (auto& n : _nodes)
	{
		result.emplace_back(n.first, &n.second);
	}
	return result;
}
const ValueTable* NetworkImpl::getValueTableByName(const std::string& name) const
{
	const ValueTable* result = nullptr;
	auto iter = _value_tables.find(name);
	if (iter != _value_tables.end())
	{
		result = &iter->second;
	}
	return result;
}
std::vector<std::pair<std::string, const ValueTable*>> NetworkImpl::getValueTables() const
{
	std::vector<std::pair<std::string, const ValueTable*>> result;
	for (auto& vt : _value_tables)
	{
		result.emplace_back(vt.first, &vt.second);
	}
	return result;
}
const Message* NetworkImpl::getMessageById(uint64_t id) const
{
	const Message* result = nullptr;
	auto iter = _messages.find(id);
	if (iter != _messages.end())
	{
		result = &iter->second;
	}
	return result;
}
std::vector<std::pair<uint64_t, const Message*>> NetworkImpl::getMessages() const
{
	std::vector<std::pair<uint64_t, const Message*>> result;
	for (const auto& m : _messages)
	{
		result.emplace_back(m.first, &m.second);
	}
	return result;
}
const EnvironmentVariable* NetworkImpl::getEnvironmentVariableByName(const std::string& name) const
{
	const EnvironmentVariable* result = nullptr;
	auto iter = _environment_variables.find(name);
	if (iter != _environment_variables.end())
	{
		result = &iter->second;
	}
	return result;
}
std::vector<std::pair<std::string, const EnvironmentVariable*>> NetworkImpl::getEnvironmentVariables() const
{
	std::vector<std::pair<std::string, const EnvironmentVariable*>> result;
	for (auto& ev : _environment_variables)
	{
		result.emplace_back(ev.first, &ev.second);
	}
	return result;
}
const AttributeDefinition* NetworkImpl::getAttributeDefinitionByName(const std::string& name) const
{
	const AttributeDefinition* result = nullptr;
	auto iter = _attribute_definitions.find(name);
	if (iter != _attribute_definitions.end())
	{
		result = &iter->second;
	}
	return result;
}
std::vector<std::pair<std::string, const AttributeDefinition*>> NetworkImpl::getAttributeDefinitions() const
{
	std::vector<std::pair<std::string, const AttributeDefinition*>> result;
	for (auto& ad : _attribute_definitions)
	{
		result.emplace_back(ad.first, &ad.second);
	}
	return result;
}
const Attribute* NetworkImpl::getAttributeDefaultByName(const std::string& name) const
{
	const Attribute* result = nullptr;
	auto iter = _attribute_defaults.find(name);
	if (iter != _attribute_defaults.end())
	{
		result = &iter->second;
	}
	return result;
}
std::vector<std::pair<std::string, const Attribute*>> NetworkImpl::getAttributeDefaults() const
{
	std::vector<std::pair<std::string, const Attribute*>> result;
	for (auto& ad : _attribute_defaults)
	{
		result.emplace_back(ad.first, &ad.second);
	}
	return result;
}
const Attribute* NetworkImpl::getAttributeValueByName(const std::string& name) const
{
	const Attribute* result = nullptr;
	auto iter = _attribute_values.find(name);
	if (iter != _attribute_values.end())
	{
		result = &iter->second;
	}
	return result;
}
std::vector<std::pair<std::string, const Attribute*>> NetworkImpl::getAttributeValues() const
{
	std::vector<std::pair<std::string, const Attribute*>> result;
	for (auto& av : _attribute_values)
	{
		result.emplace_back(av.first, &av.second);
	}
	return result;
}
const std::string& NetworkImpl::getComment() const
{
	return _comment;
}
const Message* NetworkImpl::findParentMessage(const Signal* sig) const
{
	const Message* result = nullptr;
	for (const auto& p : _messages)
	{
		const MessageImpl& msg = p.second;
		auto iter = msg.signals().find(sig->getName());
		if (iter != msg.signals().end() && &iter->second == sig)
		{
			result = &msg;
			break;
		}
	}
	return result;
}
std::string& NetworkImpl::version()
{
	return _version;
}
std::set<std::string>& NetworkImpl::newSymbols()
{
	return _new_symbols;
}
BitTimingImpl& NetworkImpl::bitTiming()
{
	return _bit_timing;
}
std::map<std::string, NodeImpl>& NetworkImpl::nodes()
{
	return _nodes;
}
std::map<std::string, ValueTableImpl>& NetworkImpl::valueTables()
{
	return _value_tables;
}
std::unordered_map<uint64_t, MessageImpl>& NetworkImpl::messages()
{
	return _messages;
}
std::map<std::string, EnvironmentVariableImpl>& NetworkImpl::environmentVariables()
{
	return _environment_variables;
}
std::map<std::string, AttributeDefinitionImpl>& NetworkImpl::attributeDefinitions()
{
	return _attribute_definitions;
}
std::map<std::string, AttributeImpl>& NetworkImpl::attributeDefaults()
{
	return _attribute_defaults;
}
std::map<std::string, AttributeImpl>& NetworkImpl::attributeValues()
{
	return _attribute_values;
}
std::string& NetworkImpl::comment()
{
	return _comment;
}
void Network::merge(std::unique_ptr<Network>&& other)
{
	auto& self = static_cast<NetworkImpl&>(*this);
	auto& o = static_cast<NetworkImpl&>(*other);
	for (auto& ns : o.newSymbols())
	{
		self.newSymbols().insert(std::move(ns));
	}
	for (auto& n : o.nodes())
	{
		self.nodes().insert(std::move(n));
	}
	for (auto& vt : o.valueTables())
	{
		self.valueTables().insert(std::move(vt));
	}
	for (auto& m : o.messages())
	{
		self.messages().insert(std::move(m));
	}
	for (auto& ev : o.environmentVariables())
	{
		self.environmentVariables().insert(std::move(ev));
	}
	for (auto& ad : o.attributeDefinitions())
	{
		self.attributeDefinitions().insert(std::move(ad));
	}
	for (auto& ad : o.attributeDefaults())
	{
		self.attributeDefaults().insert(std::move(ad));
	}
	for (auto& av : o.attributeValues())
	{
		self.attributeValues().insert(std::move(av));
	}
	other.reset(nullptr);
}
void Network::serializeToStream(std::ostream& os) const
{
	os << "VERSION \"";
	if (getVersion() != "")
	{
		os << getVersion();
	}
	os << "\"";
	os << "\n";
	os << "NS_:";
	for (const auto& ns : getNewSymbols())
	{
		os << "\n " << *ns;
	}
	os << "\n";
	getBitTiming().serializeToStream(os);
	os << "\n";
	os << "BU_:";
	for (const auto& n : getNodes())
	{
		os << " " << n.second->getName(); 
	}
	for (const auto& vt : getValueTables())
	{
		os << "\n";
		vt.second->serializeToStream(os);
	}
	for (const auto& m : getMessages())
	{
		os << "\n";
		m.second->serializeToStream(os);
	}
	// serialize message_transmitters
	for (const auto& m : getMessages())
	{
		auto transmitters = m.second->getMessageTransmitters();
		if (transmitters.size())
		{
			os << "\n";
			os << "BO_TX_BU_ " << m.second->getId() << " :";
			auto iter = transmitters.begin();
			os << " " << **iter;
			for (iter++; iter != transmitters.end(); iter++)
			{
				os << ", " << **iter;
			}
			os << ";";
		}
	}
	for (const auto& ev : getEnvironmentVariables())
	{
		os << "\n";
		ev.second->serializeToStream(os);
	}
	for (const auto& ev : getEnvironmentVariables())
	{
		if (ev.second->getVarType() == EnvironmentVariable::VarType::Data)
		{
			os << "\n";
			os << "ENVVAR_DATA_ " << ev.second->getName() << " : " << ev.second->getDataSize() << ";";
		}
	}
	for (const auto& vt : getValueTables())
	{
		if (vt.second->getSignalType())
		{
			os << "\n";
			vt.second->getSignalType()->serializeToStream(os);
		}
	}
	// serialize comments
	// Network comment
	if (getComment() != "")
	{
		os << "\n";
		os << "CM_ \"" << getComment() << "\";";
	}
	// Node comments
	for (const auto& n : getNodes())
	{
		if (n.second->getComment() != "")
		{
			os << "\n";
			os << "CM_ BU_ " << n.second->getName() << " \"" << n.second->getComment() << "\"" << ";";
		}
	}
	// Message comments
	for (const auto& m : getMessages())
	{
		if (m.second->getComment() != "")
		{
			os << "\n";
			os << "CM_ BO_ " << m.second->getId() << " \"" << m.second->getComment() << "\"" << ";";
		}
	}
	// Signal comments
	for (const auto& m : getMessages())
	{
		for (const auto& s : m.second->getSignals())
		{
			if (s.second->getComment() != "")
			{
				os << "\n";
				os << "CM_ SG_ " << m.second->getId() << " " << s.second->getName() << " \"" << s.second->getComment() << "\"" << ";";
			}
		}
	}
	// EnvironmentVariable comments
	for (const auto& ev : getEnvironmentVariables())
	{
		if (ev.second->getComment() != "")
		{
			os << "\n";
			os << "CM_ EV_ " << ev.second->getName() << " \"" << ev.second->getComment() << "\"" << ";";
		}
	}
	for (const auto& ad : getAttributeDefinitions())
	{
		os << "\n";
		ad.second->serializeToStream(os);
	}
	for (const auto& ad : getAttributeDefaults())
	{
		os << "\n";
		ad.second->serializeToStream(os, *this);
	}
	// Serialize Attribute Values
	for (const auto& val : getAttributeValues())
	{
		os << "\n";
		val.second->serializeToStream(os, *this);
	}
	for (const auto& n : getNodes())
	{
		for (const auto& val : n.second->getAttributeValues())
		{
			os << "\n";
			val.second->serializeToStream(os, *this);
		}
	}
	for (const auto& m : getMessages())
	{
		for (const auto& val : m.second->getAttributeValues())
		{
			os << "\n";
			val.second->serializeToStream(os, *this);
		}
	}
	for (const auto& m : getMessages())
	{
		for (const auto& s : m.second->getSignals())
		{
			for (const auto& val : s.second->getAttributeValues())
			{
				os << "\n";
				val.second->serializeToStream(os, *this);
			}
		}
	}
	for (const auto& ev : getEnvironmentVariables())
	{
		for (const auto& val : ev.second->getAttributeValues())
		{
			os << "\n";
			val.second->serializeToStream(os, *this);
		}
	}
	// Serialize value descriptions
	for (const auto& m : getMessages())
	{
		for (const auto& s : m.second->getSignals())
		{
			auto vds = s.second->getValueDescriptions();
			if (vds.size())
			{
				os << "\n";
				os << "VAL_ " << m.second->getId() << " " << s.second->getName();
				for (const auto& vd : vds)
				{
					os << " " << vd.first << " \"" << *vd.second << "\"";
				}
				os << ";";
			}
		}
	}
	for (const auto& ev : getEnvironmentVariables())
	{
		auto vds = ev.second->getValueDescriptions();
		if (vds.size())
		{
			os << "\n";
			os << "VAL_ " << ev.second->getName();
			for (const auto& vd : vds)
			{
				os << " " << vd.first << " \"" << *vd.second << "\"";
			}
			os << ";";
		}
	}
	for (const auto& m : getMessages())
	{
		for (const auto& s : m.second->getSignals())
		{
			if (s.second->getExtendedValueType() != Signal::ExtendedValueType::Integer)
			{
				uint64_t type = 0;
				switch (s.second->getExtendedValueType())
				{
				case Signal::ExtendedValueType::Float: type = 1; break;
				case Signal::ExtendedValueType::Double: type = 2; break;
				}
				os << "\n";
				os << "SIG_VALTYPE_ " << m.second->getId() << " " << s.second->getName() << " : " << type << ";";
			}
		}
	}
}