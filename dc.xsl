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

  $Id: dc.xsl,v 1.1 2006/04/12 16:32:53 stievie Exp $
-->

<!--
  XML Stylesheet to parse Dublin Core (http://dublincore.org/documents/dces/) XML
  files. For more informations see marc21.xsl.
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="becmn.xsl"/>

<xsl:output method="xml" indent="yes"/>

<xsl:template match="/">

<xsl:for-each select="record-list/dc-record">
  <record>

    <xsl:if test="title">
      <title><xsl:value-of select="title"/></title>
    </xsl:if>
    
    <xsl:if test="creator">
      <author>
        <xsl:call-template name="swap-names">
          <xsl:with-param name="names" select="creator"/>
        </xsl:call-template>
      </author>
    </xsl:if>
    
    <xsl:if test="contributor">
      <xsl:if test="not(author)">
        <!-- No author use contributor as author -->
        <author>
          <xsl:call-template name="swap-names">
            <xsl:with-param name="names" select="contributor"/>
          </xsl:call-template>
        </author>
      </xsl:if>
      
      <contributor><xsl:value-of select="contributor"/></contributor>
    </xsl:if>
    
    <xsl:if test="publisher">
      <publisher><xsl:value-of select="publisher"/></publisher>
    </xsl:if>
    
    <xsl:if test="date">
      <year><xsl:value-of select="date"/></year>
    </xsl:if>
    
    <xsl:if test="description">
      <description><xsl:value-of select="description"/></description>
    </xsl:if>
    
  </record>
</xsl:for-each>

</xsl:template>
</xsl:stylesheet>
