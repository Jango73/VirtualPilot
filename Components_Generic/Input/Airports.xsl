<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
	version="2.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:navaid="http://navaid.com/GPX/NAVAID/1/0"
	>
	<xsl:template match="/">
		<xsl:for-each select="gpx/wpt">
			<xsl:text>&#xa;</xsl:text>
			<Airport>
				<xsl:attribute name="ID"><xsl:value-of select="name"/></xsl:attribute>
				<xsl:attribute name="Name"><xsl:value-of select="extensions/navaid:name"/></xsl:attribute>
				<xsl:attribute name="MagVar"><xsl:value-of select="magvar"/></xsl:attribute>
				<xsl:text>&#xa;</xsl:text>
				<Geoloc>
					<xsl:attribute name="Latitude"><xsl:value-of select="@lat"/></xsl:attribute>
					<xsl:attribute name="Longitude"><xsl:value-of select="@lon"/></xsl:attribute>
					<xsl:attribute name="Altitude"><xsl:value-of select="ele"/></xsl:attribute>
				</Geoloc>
				<xsl:for-each select="extensions/navaid:frequencies/navaid:frequency">
					<xsl:text>&#xa;</xsl:text>
					<Radio>
						<xsl:choose>
							<xsl:when test="@type = 'APP'">
								<xsl:attribute name="Type">Approach</xsl:attribute>
							</xsl:when>
							<xsl:when test="@type = 'ATIS'">
								<xsl:attribute name="Type">ATIS</xsl:attribute>
							</xsl:when>
							<xsl:when test="@type = 'DEP'">
								<xsl:attribute name="Type">Departure</xsl:attribute>
							</xsl:when>
							<xsl:when test="@type = 'GND'">
								<xsl:attribute name="Type">Ground</xsl:attribute>
							</xsl:when>
							<xsl:when test="@type = 'TWR'">
								<xsl:attribute name="Type">Tower</xsl:attribute>
							</xsl:when>
							<xsl:otherwise>
								<xsl:attribute name="Type">Unknown</xsl:attribute>
							</xsl:otherwise>
						</xsl:choose>
						<xsl:attribute name="Frequency"><xsl:value-of select="@frequency"/></xsl:attribute>
					</Radio>
				</xsl:for-each>
				<xsl:for-each select="extensions/navaid:runways/navaid:runway">
					<xsl:text>&#xa;</xsl:text>
					<Runway>
						<xsl:attribute name="ID"><xsl:value-of select="@designation"/></xsl:attribute>
						<xsl:attribute name="Length"><xsl:value-of select="@length"/></xsl:attribute>
						<xsl:attribute name="Width"><xsl:value-of select="@width"/></xsl:attribute>
						<xsl:attribute name="Heading"><xsl:value-of select="navaid:beginning/navaid:heading"/></xsl:attribute>
						<Geoloc>
							<xsl:attribute name="Latitude"><xsl:value-of select="navaid:beginning/@lat"/></xsl:attribute>
							<xsl:attribute name="Longitude"><xsl:value-of select="navaid:beginning/@lon"/></xsl:attribute>
							<xsl:attribute name="Altitude"><xsl:value-of select="navaid:beginning/navaid:elev"/></xsl:attribute>
						</Geoloc>
					</Runway>
				</xsl:for-each>
			<xsl:text>&#xa;</xsl:text>
			</Airport>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
