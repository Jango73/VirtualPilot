<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
	version="2.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:navaid="http://navaid.com/GPX/NAVAID/1/0"
	>
	<xsl:template match="/">
		<xsl:for-each select="gpx/wpt">
			<xsl:text>&#xa;</xsl:text>
			<Navaid>
				<xsl:attribute name="ID"><xsl:value-of select="name"/></xsl:attribute>
				<xsl:choose>
					<xsl:when test="type = 'NDB'">
						<xsl:attribute name="Type">NDB</xsl:attribute>
					</xsl:when>
					<xsl:when test="type = 'VOR'">
						<xsl:attribute name="Type">VOR</xsl:attribute>
					</xsl:when>
					<xsl:when test="type = 'VOR/DME'">
						<xsl:attribute name="Type">VOR-DME</xsl:attribute>
					</xsl:when>
					<xsl:when test="type = 'VORTAC'">
						<xsl:attribute name="Type">VOR-TAC</xsl:attribute>
					</xsl:when>
				</xsl:choose>
				<xsl:attribute name="Frequency"><xsl:value-of select="extensions/navaid:frequencies/navaid:frequency/@frequency"/></xsl:attribute>
				<xsl:attribute name="Name"><xsl:value-of select="extensions/navaid:name"/></xsl:attribute>
				<xsl:attribute name="MagVar"><xsl:value-of select="magvar"/></xsl:attribute>
				<Geoloc>
					<xsl:attribute name="Latitude"><xsl:value-of select="@lat"/></xsl:attribute>
					<xsl:attribute name="Longitude"><xsl:value-of select="@lon"/></xsl:attribute>
					<xsl:attribute name="Altitude"><xsl:value-of select="0"/></xsl:attribute>
				</Geoloc>
			</Navaid>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
