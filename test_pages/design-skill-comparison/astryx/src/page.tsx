// Scaffolded from the Astryx `centered-hero` page template
// (`astryx template centered-hero --type page src`). The template frame is kept:
// Layout > LayoutContent padding 6 > VStack gap 10, a centered hero stack
// (gap 6 / gap 3) and a transparent Section in the picture slot, which now holds
// the product preview instead of an image.
//
// Layout contract
//   frame:    AppShell (TopNav, sticky, height auto) > Layout capped at 1200
//   content:  sections stack in one column; grids reflow with Grid {minWidth, max}
//   <md:      TopNav collapses into AppShell's generated mobile drawer
//   <=640:    product preview drops the log table's service column
//   anchors:  the driftlog theme gives Text/Heading a scroll margin that clears
//             the sticky TopNav (src/themes/driftlog/driftlogTheme.ts)

import { AppShell } from "@astryxdesign/core/AppShell";
import { Button } from "@astryxdesign/core/Button";
import { Card } from "@astryxdesign/core/Card";
import { Code } from "@astryxdesign/core/Code";
import { Collapsible, CollapsibleGroup } from "@astryxdesign/core/Collapsible";
import { Divider } from "@astryxdesign/core/Divider";
import { Grid } from "@astryxdesign/core/Grid";
import { Icon } from "@astryxdesign/core/Icon";
import {
	HStack,
	Layout,
	LayoutContent,
	LayoutFooter,
	VStack,
} from "@astryxdesign/core/Layout";
import { Link } from "@astryxdesign/core/Link";
import { List, ListItem } from "@astryxdesign/core/List";
import { NavIcon } from "@astryxdesign/core/NavIcon";
import { Section } from "@astryxdesign/core/Section";
import { Heading, Text } from "@astryxdesign/core/Text";
import { Token } from "@astryxdesign/core/Token";
import { TopNav, TopNavHeading, TopNavItem } from "@astryxdesign/core/TopNav";
import { ArrowRightIcon, PlayCircleIcon } from "@heroicons/react/20/solid";
import { CommandLineIcon } from "@heroicons/react/24/outline";
import type { Feature, Plan } from "./content";
import {
	FAQS,
	FEATURES,
	FOOTER_GROUPS,
	NAV_LINKS,
	PLANS,
	STATS,
} from "./content";
import { ProductPreview } from "./ProductPreview";

function SiteNav() {
	return (
		<TopNav
			label="주 메뉴"
			heading={
				<TopNavHeading
					heading="Driftlog"
					headingHref="#top"
					logo={<NavIcon icon={<Icon icon={CommandLineIcon} size="sm" />} />}
				/>
			}
			startContent={
				<>
					{NAV_LINKS.map((link) => (
						<TopNavItem key={link.href} label={link.label} href={link.href} />
					))}
				</>
			}
			endContent={
				<HStack gap={2} vAlign="center">
					<Button label="로그인" variant="ghost" href="#" />
					<Button label="무료로 시작" variant="primary" href="#pricing" />
				</HStack>
			}
		/>
	);
}

function SectionHeader({
	id,
	title,
	description,
}: {
	id?: string;
	title: string;
	description?: string;
}) {
	return (
		<VStack gap={3} hAlign="center">
			<Heading level={2} id={id} justify="center" textWrap="balance">
				{title}
			</Heading>
			{description ? (
				<Text color="secondary" justify="center" textWrap="balance">
					{description}
				</Text>
			) : null}
		</VStack>
	);
}

function FeatureItem({ feature }: { feature: Feature }) {
	return (
		<VStack gap={3}>
			<HStack gap={2} vAlign="center">
				<Icon icon={feature.icon} size="md" color="accent" />
				<Text type="label" color="secondary">
					{feature.name}
				</Text>
			</HStack>
			<VStack gap={2}>
				<Heading level={3}>{feature.title}</Heading>
				<Text color="secondary">{feature.body}</Text>
			</VStack>
			<Text type="supporting">
				<Code>{feature.snippet}</Code>
			</Text>
		</VStack>
	);
}

function PlanCard({ plan }: { plan: Plan }) {
	return (
		<Card elevation={plan.isRecommended ? "med" : "none"}>
			<VStack gap={5}>
				<VStack gap={1}>
					<HStack gap={2} vAlign="center">
						<Heading level={3}>{plan.name}</Heading>
						{plan.isRecommended ? (
							<Token size="sm" label="추천" color="blue" />
						) : null}
					</HStack>
					<Text color="secondary">{plan.summary}</Text>
				</VStack>
				<HStack gap={1} vAlign="end">
					<Text type="display-3" hasTabularNumbers>
						{plan.price}
					</Text>
					{plan.period ? <Text color="secondary">{plan.period}</Text> : null}
				</HStack>
				<Button
					label={plan.cta}
					variant={plan.isRecommended ? "primary" : "secondary"}
					width="100%"
					href="#"
				/>
				<Divider />
				<List density="compact" edge="flush">
					{plan.features.map((item) => (
						<ListItem
							key={item}
							label={item}
							startContent={<Icon icon="check" size="sm" color="success" />}
						/>
					))}
				</List>
			</VStack>
		</Card>
	);
}

function SiteFooter() {
	return (
		<LayoutFooter hasDivider padding={6} label="사이트 정보">
			<VStack gap={6}>
				<Grid columns={{ minWidth: 140, max: 4 }} gap={6}>
					<VStack gap={2}>
						<HStack gap={2} vAlign="center">
							<NavIcon icon={<Icon icon={CommandLineIcon} size="sm" />} />
							<Text weight="semibold">Driftlog</Text>
						</HStack>
						<Text type="supporting">팀을 위한 로그 수집·검색·알림</Text>
					</VStack>
					{FOOTER_GROUPS.map((group) => (
						<VStack key={group.title} gap={2}>
							<Text type="label">{group.title}</Text>
							{group.links.map((link) => (
								<Link
									key={link.label}
									href={link.href}
									type="supporting"
									color="secondary"
								>
									{link.label}
								</Link>
							))}
						</VStack>
					))}
				</Grid>
				<Divider />
				<HStack gap={3} hAlign="between" wrap="wrap">
					<Text type="supporting">© 2026 Driftlog</Text>
					<Text type="supporting">
						Driftlog는 디자인 비교용 가상 제품이며, 표시된 수치는 예시입니다.
					</Text>
				</HStack>
			</VStack>
		</LayoutFooter>
	);
}

export default function LandingPage() {
	return (
		<AppShell height="auto" variant="section" topNav={<SiteNav />}>
			<Layout
				height="auto"
				contentWidth={1200}
				footer={<SiteFooter />}
				content={
					<LayoutContent padding={6}>
						<VStack gap={10}>
							{/* Hero: the template's centered stack. */}
							<VStack gap={6} hAlign="center" paddingBlockStart={10}>
								<VStack gap={3} hAlign="center" maxWidth={760}>
									<Token label="Kubernetes · VM · 베어메탈" />
									<Heading
										level={1}
										id="top"
										type="display-2"
										justify="center"
										textWrap="balance"
									>
										로그는 전부 남기고, 원인은 몇 초 만에
									</Heading>
									<Text
										type="large"
										color="secondary"
										justify="center"
										textWrap="balance"
									>
										클러스터에 경량 에이전트 하나만 붙이세요. 로그는 오브젝트
										스토리지에 저렴하게 쌓이고, 익숙한 쿼리로 바로 검색되며,
										에러가 급증하면 Slack으로 먼저 알려 드립니다.
									</Text>
								</VStack>
								<HStack gap={3} wrap="wrap" hAlign="center">
									<Button
										label="무료로 시작"
										variant="primary"
										size="lg"
										href="#pricing"
										endContent={
											<Icon icon={ArrowRightIcon} size="sm" color="inherit" />
										}
									/>
									<Button
										label="데모 보기"
										variant="secondary"
										size="lg"
										href="#demo"
										icon={<Icon icon={PlayCircleIcon} color="inherit" />}
									/>
								</HStack>
								<Text type="supporting" justify="center">
									신용카드 없이 시작 · 하루 5GB까지 무료
								</Text>
							</VStack>

							{/* The template's picture slot, now the product preview. */}
							<Section variant="transparent" padding={6} paddingBlock={0}>
								<VStack gap={3}>
									<Text type="supporting" justify="center" id="demo">
										제품 미리보기 · 쿼리와 레벨 필터를 직접 바꿔 보세요
									</Text>
									<ProductPreview />
								</VStack>
							</Section>

							<Section variant="transparent" padding={6} paddingBlock={10}>
								<VStack gap={8}>
									<SectionHeader
										id="features"
										title="수집부터 알림까지, 도구 하나로"
										description="따로 붙일 파이프라인 없이, 백엔드·플랫폼 엔지니어가 매일 하는 네 가지 일을 한곳에서 끝냅니다."
									/>
									<Grid columns={{ minWidth: 240, max: 4 }} gap={8}>
										{FEATURES.map((feature) => (
											<FeatureItem key={feature.id} feature={feature} />
										))}
									</Grid>
								</VStack>
							</Section>

							<Section variant="transparent" padding={6} paddingBlock={0}>
								<VStack gap={4}>
									<Grid columns={{ minWidth: 220, max: 3 }} gap={4}>
										{STATS.map((stat) => (
											<Card key={stat.label} variant="muted">
												<VStack gap={1}>
													<Text type="display-2" hasTabularNumbers>
														{stat.value}
													</Text>
													<Text weight="semibold">{stat.label}</Text>
													<Text type="supporting">{stat.detail}</Text>
												</VStack>
											</Card>
										))}
									</Grid>
									<Text type="supporting" justify="center">
										베타 고객 운영 환경에서 측정한 예시 수치이며, 워크로드에
										따라 달라질 수 있습니다.
									</Text>
								</VStack>
							</Section>

							<Section variant="transparent" padding={6} paddingBlock={10}>
								<VStack gap={8}>
									<SectionHeader
										id="pricing"
										title="팀 규모에 맞춰 시작하세요"
										description="모든 요금제에 라이브 테일과 Slack 알림이 포함됩니다. 가격은 부가세 별도입니다."
									/>
									<Grid columns={{ minWidth: 280, max: 3 }} gap={4}>
										{PLANS.map((plan) => (
											<PlanCard key={plan.id} plan={plan} />
										))}
									</Grid>
								</VStack>
							</Section>

							<Section variant="transparent" padding={6} paddingBlock={0}>
								<VStack gap={6} hAlign="center">
									<SectionHeader id="faq" title="자주 묻는 질문" />
									<VStack gap={0} maxWidth={760} width="100%">
										<CollapsibleGroup
											type="single"
											hasDividers
											defaultValue={FAQS[0].id}
										>
											{FAQS.map((faq) => (
												<Collapsible
													key={faq.id}
													value={faq.id}
													trigger={
														<Text type="body" weight="semibold">
															{faq.question}
														</Text>
													}
												>
													<Text type="body" color="secondary">
														{faq.answer}
													</Text>
												</Collapsible>
											))}
										</CollapsibleGroup>
									</VStack>
								</VStack>
							</Section>

							<Section variant="muted" padding={10}>
								<VStack gap={6} hAlign="center">
									<VStack gap={3} hAlign="center">
										<Heading level={2} justify="center" textWrap="balance">
											에이전트 설치는 5분이면 끝납니다
										</Heading>
										<Text color="secondary" justify="center" textWrap="balance">
											Free 요금제로 시작하고, 팀이 커지면 언제든 올리세요.
											신용카드는 필요 없습니다.
										</Text>
									</VStack>
									<HStack gap={3} wrap="wrap" hAlign="center">
										<Button
											label="무료로 시작"
											variant="primary"
											size="lg"
											href="#pricing"
											endContent={
												<Icon icon={ArrowRightIcon} size="sm" color="inherit" />
											}
										/>
										<Button
											label="데모 보기"
											variant="secondary"
											size="lg"
											href="#demo"
										/>
									</HStack>
								</VStack>
							</Section>
						</VStack>
					</LayoutContent>
				}
			/>
		</AppShell>
	);
}
