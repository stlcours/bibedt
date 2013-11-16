<?xml version="1.0" encoding="UTF-8"?>
<!--
  BibEdt
  Copyright (C) 2005, Ascher Stefan. All rights reserved.
  stievie[at]users[dot]sourceforge[dot]net, http://bibedt.sourceforge.net/

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  $Id: becmn.xsl,v 1.9 2006/08/12 17:28:56 stievie Exp $
-->

<!--
  Commonly used templates.
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template name="trim-left">
  <!-- Remove strChars from strInput at start -->
  <xsl:param name="strInput" select="''"/>
  <xsl:param name="strChars" select="' '"/>
  <xsl:variable name="strLen" select="string-length($strInput)"/>
  <xsl:variable name="strOutput" select="substring($strInput, 2, $strLen - 1)"/>
  <xsl:variable name="strFirstChar" select="substring($strInput, 1, 1)"/>

  <xsl:choose>
    <xsl:when test="contains($strChars,$strFirstChar)">
      <xsl:call-template name="trim-left" >
        <xsl:with-param name="strInput" select="$strOutput"/>
        <xsl:with-param name="strChars" select="$strChars"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$strInput"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="conv-url">
  <!-- Make a real URL -->
  <xsl:param name="str" select="''"/>
  <xsl:choose>
    <xsl:when test="contains($str,'\url{')">
      <xsl:value-of select="substring-before($str,'\url{')"/>
      <xsl:variable name="url" select="substring-before(substring-after($str,'\url{'),'}')"/> 
      <kbd><a href="{$url}"><xsl:value-of select="$url"/></a></kbd>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$str"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="trim-right">
  <!-- Remove strChars from strInput at end -->
  <xsl:param name="strInput" select="''"/>
  <xsl:param name="strChars" select="' '"/>
  <xsl:variable name="strLen" select="string-length($strInput)" />
  <xsl:variable name="strOutput" select="substring($strInput, 1, $strLen - 1)" />
  <xsl:variable name="strLastChar" select="substring($strInput, $strLen, 1)" />

  <xsl:choose>
    <xsl:when test="contains($strChars,$strLastChar)">
      <xsl:call-template name="trim-right">
        <xsl:with-param name="strInput" select="$strOutput"/>
        <xsl:with-param name="strChars" select="$strChars"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$strInput" />
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="trim">
  <!-- Remove strChars from strInput at start and end -->
  <xsl:param name="strInput" select="''"/>
  <xsl:param name="strChars" select="' '"/>
  <xsl:variable name="InputL">
    <xsl:call-template name="trim-left" >
      <xsl:with-param name="strInput" select="$strInput"/>
      <xsl:with-param name="strChars" select="$strChars"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="InputR">
    <xsl:call-template name="trim-right" >
      <xsl:with-param name="strInput" select="$InputL"/>
      <xsl:with-param name="strChars" select="$strChars"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:value-of select="$InputR" />
</xsl:template>

<xsl:template name="remove-garb">
  <!-- Remove garbage at start and end -->
  <xsl:param name="str"/>
  <xsl:param name="chars" select="' .,[]/:'"/>
  <xsl:call-template name="trim" >
    <xsl:with-param name="strInput" select="$str"/>
    <xsl:with-param name="strChars" select="$chars"/>
  </xsl:call-template>
</xsl:template>

<xsl:template name="swap-names">
  <!-- Surename, Forename -> Forename Surename -->
  <xsl:param name="names"/>
  <xsl:variable name="raw-names" select="normalize-space($names)"/>

  <xsl:choose>
    <xsl:when test="contains($raw-names,', ')">
      <xsl:variable name="res" select="concat(substring-after($raw-names,', '),' ',substring-before($raw-names,', '))"/>
      <xsl:call-template name="remove-garb">
        <xsl:with-param name="str" select="$res"/>
        <xsl:with-param name="chars" select="' .,[]/:-1234567890'"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$raw-names"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="str-replace">
  <!-- Replace old in str with new -->
  <xsl:param name="str"/>
  <xsl:param name="old"/>
  <xsl:param name="new"/>
  <xsl:choose>
    <xsl:when test="contains($str,$old)">
      <xsl:variable name="res" select="concat(substring-before($str,$old),$new,substring-after($str,$old))"/>
      <xsl:call-template name="str-replace">
        <xsl:with-param name="str" select="$res"/>
        <xsl:with-param name="old" select="$old"/>
        <xsl:with-param name="new" select="$new"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$str"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="format-names">
  <!-- Format names: Replace all ' and ' with ', ' except the last -->
  <xsl:param name="names"/>
  <xsl:variable name="raw-names" select="normalize-space($names)"/>
  <xsl:choose>
    <xsl:when test="contains($raw-names,' and ') and contains(substring-after($raw-names,' and '),' and ')">
      <xsl:value-of select="concat(substring-before($raw-names,' and '),', ')"/>
      <xsl:call-template name="format-names">
        <xsl:with-param name="names" select="substring-after($raw-names,' and ')"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$raw-names"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template name="add-punct">
  <!-- Add a punctuation mark if there isn't already one -->
  <xsl:param name="val"/>
  <xsl:param name="punct" select="'.'"/>
  <xsl:variable name="strLen" select="string-length($val)" />
  <xsl:variable name="strLastChar" select="substring($val, $strLen, 1)" />
  <xsl:if test="not(contains('?.!', $strLastChar))">
    <xsl:value-of select="$punct"/>
  </xsl:if>
</xsl:template>

<xsl:template name="substring-after-last">
  <xsl:param name="text"/>
  <xsl:param name="chars"/>

  <xsl:choose>
    <xsl:when test="contains($text, $chars)">
      <xsl:variable name="last" select="substring-after($text, $chars)"/>
  	  <xsl:choose>
  	    <xsl:when test="contains($last, $chars)">
  	      <xsl:call-template name="substring-after-last">
  	        <xsl:with-param name="text" select="$last"/>
  	        <xsl:with-param name="chars" select="$chars"/>
  	      </xsl:call-template>
  	    </xsl:when>
  	    <xsl:otherwise>
  	      <xsl:value-of select="$last"/>
  	    </xsl:otherwise>
  	  </xsl:choose>
    </xsl:when>

    <xsl:otherwise>
      <xsl:value-of select="$text"/>
    </xsl:otherwise>

  </xsl:choose>
</xsl:template>

<xsl:variable name="str-lower-chars" select="'abcdefghijklmnopqrstuvwxyz'"/>
<xsl:variable name="str-upper-chars" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>

<xsl:template name="to-upper">
  <xsl:param name="text"/>
  <xsl:value-of select="translate($text, $str-lower-chars, $str-upper-chars)"/>
</xsl:template>

<xsl:template name="to-lower">
  <xsl:param name="text"/>
  <xsl:value-of select="translate($text, $str-upper-chars, $str-lower-chars)"/>
</xsl:template>

</xsl:stylesheet>
