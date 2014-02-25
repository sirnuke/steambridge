#!/usr/bin/env ruby
# convert.rb - Ruby tool for generating the wrapping classes

INDENT = '  '

# In bytes, of course
VOID_SIZE = 0
BYTE_SIZE = 1
SHORT_SIZE = 2
POINTER_SIZE = 4
FLOAT_SIZE = 4
INT_SIZE = 4
DOUBLE_SIZE = 8
LONG_LONG_SIZE = 8

def err(msg)
  puts "#{$0}: #{msg}"
  exit(1)
end

def warn(msg)
  puts "Warning: #{msg}"
end

def describe(type)
  pointer = false
  ppointer = false
  if type.match(/\*\*/)
    ppointer = true
    type.chomp!('**')
  elsif type.end_with?('*')
    type.chomp!('*')
    pointer = true
  end
  data = { :type => type, :printf => "%i", :size => INT_SIZE, :float => false, :const => false, :default => nil , :struct => false }
  case type
  when 'constchar'
    data[:type] = 'const char'
    data[:const] = true
    data[:printf] = "\\\"%s\\\""
    data[:size] = BYTE_SIZE
  when 'constvoid'
    data[:type] = 'const void'
    err "const void is expected to be a pointer" unless pointer or ppointer
  when 'constint32'
    data[:type] = 'const int32'
    data[:const] = true
  when 'uint32'
    data[:printf] = "%u"
  when 'bool'
    data[:size] = BYTE_SIZE
  when 'char'
    data[:size] = BYTE_SIZE
    data[:printf] = "%c"
  when 'uint8'
    data[:printf] = "%hhu"
    data[:size] = BYTE_SIZE
  when 'uint16'
    data[:printf] = "%hu"
    data[:size] = SHORT_SIZE
  when 'int64'
    data[:printf] = "%lli"
    data[:size] = LONG_LONG_SIZE
  when 'SteamAPICall_t' # uint64
    data[:printf] = "%llu"
    data[:size] = LONG_LONG_SIZE
  when 'CSteamID' # effective uint64
    data[:printf] = "%llu"
    data[:size] = LONG_LONG_SIZE
    data[:struct] = true
  when 'CGameID' # effective uint64
    data[:printf] = "%llu"
    data[:size] = LONG_LONG_SIZE
    data[:struct] = true
  when 'HSteamUser' # int32
  when 'HSteamPipe' # int32
  when 'HAuthTicket' # uint32
    data[:printf] = "%u"
  when 'AppId_t' # uint32
    data[:printf] = "%u"
  when 'DepotId_t' # uint32
    data[:printf] = "%u"
  when 'UGCHandle_t' # uint64
    data[:printf] = "%llu"
    data[:size] = LONG_LONG_SIZE
  when 'FriendGameInfo_t'
    err "FriendGameInfo_t is expected to be a pointer" unless pointer or ppointer
  when 'LeaderboardEntry_t'
    err "LeaderboardEntry_t is expected to be a pointer" unless pointer or ppointer
  when 'SteamLeaderboardEntries_t' # uin64
    data[:printf] = "%llu"
    data[:size] = LONG_LONG_SIZE
  when 'SteamLeaderboard_t' # uint64
    data[:printf] = "%llu"
    data[:size] = LONG_LONG_SIZE
  when 'void'
    data[:size] = VOID_SIZE
  when 'SteamAPIWarningMessageHook_t'
    data[:printf] = "0x%p"
    data[:size] = POINTER_SIZE
  when 'double'
    data[:printf] = "%f"
    data[:size] = DOUBLE_SIZE
    data[:float] = true
  when 'float'
    data[:printf] = "%f"
    data[:size] = FLOAT_SIZE
    data[:float] = true
  else
    unless type.start_with? 'E' or type == 'int' or type == 'int32' 
      warn "Possible unimplemented type of #{type}"
    end
  end
  if pointer or ppointer
    data[:size] = POINTER_SIZE
    data[:float] = false
    data[:printf] = "0x%p" unless type.match(/^const/)
  end
  if ppointer
    data[:type] += " **"
  elsif pointer
    data[:type] += " *"
  else
    data[:type] += " "
  end

  return data
end

class API
  attr_accessor :ret, :name, :args

  def initialize(line, num)
    @ret = nil
    @name = nil
    @args = []
    arg = nil
    hasdefault = false
    line.gsub!(/[\(\),;]/, ' ') # parans, commans, semicolons become a space
    line.gsub!(/ \*/, '* ') # collapse xyz * types
    line.gsub!(/\/\/.+/, '') # remove any trailing comments
    line.gsub!(/ = 0/, '') # pure virtual marker
    line.gsub!(/virtual /, '') # remove virtual
    line.gsub!(/const /, 'const') # collapse const
    line.scan(/\S+/) do |token|
      token.sub!(/[\(\),]/, '')
      next if token.empty?
      if @ret.nil?
        @ret = describe token
      elsif @name.nil?
        @name = token
      elsif arg.nil?
        # Yuck
        if hasdefault
          hasdefault = false
          @args.last[:default] = token
        elsif token == '='
          hasdefault = true
        else
          arg = token
        end
      else
        data = describe(arg)
        data[:name] = token
        @args << data
        arg = nil
      end
    end
    if @ret.nil? or @name.nil?
      err "Error on line #{num} - missing return or name"
    end
  end

  def to_s
    res = "#{@ret}: #{@name}\t("
    @args.each do |arg|
      res += "\t" unless arg == @args.first
      res += "#{arg[:ret]}: #{arg[:name]}"
    end
    res += ")"
    return res
  end
end

err "Requires one argument, the spec filename." if ARGV.count == 0
file = ARGV[0]
err "#{file} doesn't exist!" unless File.exist?(file)

name = nil
apis = []
num = 0

File.open(file, 'r') do |file|
  file.each_line do |line|
    num += 1
    line.strip!
    next if line.start_with?('#') or line.match(/^\/\//)
    next if line.empty?
    if name.nil?
      match = /class\s+(\w+)/.match(line)
      if match
        unless match[1].match(/^ISteam/)
          warn "Unexpected class called #{name}, skipping"
        else
          name = match[1]
          name.sub! 'ISteam', ''
        end
      end
      next
    end
    next if line.include?('{') or line == 'public:'
    break if line.include?('}')
    apis << API.new(line, num)
  end
end

err "Didn't find an ISteam* class!" unless name

header = "#{name.downcase}_api.h"
source = "#{name.downcase}_api.cpp"

if File.exist?(header) or File.exist?(source)
  err "#{header} or #{source} already exists!"
end

File.open(header, 'w') do |file|
  file.puts "// #{header} - Autogenerated header for ISteam#{name}"
  file.puts "// Copyright (c) 2014 Bryan DeGrendel"
  file.puts "//"
  file.puts "// See COPYING and license/LICENSE.steambridge for license information"
  file.puts
  file.puts "#pragma once"
  file.puts
  file.puts "#include \"types.h\""
  file.puts
  file.puts "class ISteam#{name};"
  file.puts
  file.puts "class Steam#{name}"
  file.puts "{"
  file.puts "#{INDENT}public:"

  apis.each do |api|

    file.print "#{INDENT}#{INDENT}virtual "
    file.print "#{api.ret[:type]}#{api.name}(";

    api.args.each do |arg|
      file.print ", " unless arg == api.args.first
      file.print "#{arg[:type]}#{arg[:name]}"
      file.print " = #{arg[:default]}" if arg[:default]
    end
    file.puts ");"
  end
  file.puts
  file.puts "#{INDENT}#{INDENT}Steam#{name}();"
  file.puts
  file.puts "#{INDENT}private:"
  file.puts "#{INDENT}#{INDENT}ISteam#{name} *steam#{name};"
  file.puts
  file.puts "};"
end

define = "Steam#{name}::"

File.open(source, 'w') do |file|
  file.puts "// #{source} - Autogenerated source for ISteam#{name}"
  file.puts "// Copyright (c) 2014 Bryan DeGrendel"
  file.puts "//"
  file.puts "// See COPYING and license/LICENSE.steambridge for license information"
  file.puts
  file.puts "#include \"stdafx.h\""
  file.puts
  file.puts "#include \"logging.h\""
  file.puts "#include \"state.h\""
  file.puts "#include \"steam_api_proxy.h\""
  file.puts "#include \"types.h\""
  file.puts 
  file.puts "#include \"#{header}\""
  file.puts
  file.puts "#include <steam_api_bridge.h>"
  file.puts
  file.puts "#{define}Steam#{name}() : steam#{name}(NULL)"
  file.puts "{"
  file.puts "#{INDENT}__TRACE(\"(this=0x%p)\", this);"
  file.puts "#{INDENT}steam#{name} = Steam#{name}_();";
  file.puts "#{INDENT}__LOG(\"Wrapping ISteam#{name} (0x%p) into (0x%p)\", steam#{name}, this);";
  file.puts "}"
  file.puts 

  offset = 0
  apis.each do |api|
    file.print "#{api.ret[:type]}#{define}#{api.name}("

    api.args.each do |arg|
      file.print ", " unless arg == api.args.first
      file.print "#{arg[:type]}#{arg[:name]}"
    end

    file.puts ")"
    file.puts "{"
    file.print "#{INDENT}__TRACE(\"("
    api.args.each { |arg| file.print "#{arg[:printf]}," }
    file.print ")\""
    api.args.each { |arg| file.print ", #{arg[:name]}" }
    file.puts ");"

    if api.ret[:size] > VOID_SIZE
      if api.ret[:struct]
        file.puts "#{INDENT}#{api.ret[:type]}data;"
        file.puts "#{INDENT}#{api.ret[:type]}*result = &data;"
      else
        file.puts "#{INDENT}#{api.ret[:type]}result;"
      end
    end
    file.puts "#{INDENT}__asm"
    file.puts "#{INDENT}{"
    stack = 0

    api.args.reverse_each do |arg|
      file.puts "#{INDENT}#{INDENT}// Push function arguments"
      case arg[:size]
      when VOID_SIZE
        err "Unexpected argument with size VOID (?) in type #{arg[:type]}"
      when BYTE_SIZE
        file.puts "#{INDENT}#{INDENT}mov al, #{arg[:name]}"
        file.puts "#{INDENT}#{INDENT}push eax"
        stack += POINTER_SIZE
      when SHORT_SIZE
        file.puts "#{INDENT}#{INDENT}mov ax, #{arg[:name]}"
        file.puts "#{INDENT}#{INDENT}push eax"
        stack += POINTER_SIZE
      when INT_SIZE
        file.puts "#{INDENT}#{INDENT}mov eax, #{arg[:name]}"
        file.puts "#{INDENT}#{INDENT}push eax"
        stack += POINTER_SIZE
      when LONG_LONG_SIZE
        file.puts "#{INDENT}#{INDENT}lea edx, #{arg[:name]}"
        file.puts "#{INDENT}#{INDENT}mov eax, [edx+4]"
        file.puts "#{INDENT}#{INDENT}push eax"
        file.puts "#{INDENT}#{INDENT}mov eax, [edx+0]"
        file.puts "#{INDENT}#{INDENT}push eax"
        stack += LONG_LONG_SIZE
      else
        err "Unknown size of #{arg[:size]}"
      end
    end
    err "Invalid stack size of #{stack}" if stack % POINTER_SIZE != 0
    file.puts "#{INDENT}#{INDENT}// Push Linux-side 'this'"
    file.puts "#{INDENT}#{INDENT}mov eax, [this]"
    file.puts "#{INDENT}#{INDENT}mov eax, [eax]this.steam#{name}"
    file.puts "#{INDENT}#{INDENT}push eax"
    stack += POINTER_SIZE
    if api.ret[:struct]
      file.puts "#{INDENT}#{INDENT}// Push hidden pointer to result struct"
      file.puts "#{INDENT}#{INDENT}mov edx, result"
      file.puts "#{INDENT}#{INDENT}push edx"
      # GCC pops the hidden pointer in the function
      # Why?  Because REASONS
    end
    file.puts "#{INDENT}#{INDENT}// Get the vtable (pointer at this)"
    file.puts "#{INDENT}#{INDENT}mov eax, [eax]"
    file.puts "#{INDENT}#{INDENT}// Lookup the pointer in the vtable"
    file.puts "#{INDENT}#{INDENT}mov eax, [eax+#{offset}]"
    file.puts "#{INDENT}#{INDENT}// Call that memory location"
    file.puts "#{INDENT}#{INDENT}call eax"
    file.puts "#{INDENT}#{INDENT}// Move the returned value into the result"
    if api.ret[:struct]
      file.puts "#{INDENT}#{INDENT}// (Return value is a hidden struct, should already be set)"
    elsif api.ret[:float]
      file.puts "#{INDENT}#{INDENT}fst result"
    else
      case api.ret[:size]
      when VOID_SIZE
      when BYTE_SIZE
        file.puts "#{INDENT}#{INDENT}mov result, al"
      when SHORT_SIZE
        file.puts "#{INDENT}#{INDENT}mov result, ax"
      when INT_SIZE
        file.puts "#{INDENT}#{INDENT}mov result, eax"
      when LONG_LONG_SIZE
        file.puts "#{INDENT}#{INDENT}lea ecx, result"
        file.puts "#{INDENT}#{INDENT}mov [ecx+0], eax"
        file.puts "#{INDENT}#{INDENT}mov [ecx+4], edx"
      else
        err "Unknown size of #{api.ret[:size]}"
      end
    end
    file.puts "#{INDENT}#{INDENT}// restore stack"
    file.puts "#{INDENT}#{INDENT}add esp, #{stack}"
    file.puts "#{INDENT}}"
    if api.ret[:struct]
      file.puts "#{INDENT}__TRACE(\"Return value is #{api.ret[:printf]}\", data);"
      file.puts "#{INDENT}return data;"
    else
      file.puts "#{INDENT}return result;" unless api.ret[:size] == VOID_SIZE
    end
    file.puts "}"
    file.puts
    offset += POINTER_SIZE
  end

  file.puts "#include \"#{name.downcase}_api_code.inc\""
  file.puts
end

